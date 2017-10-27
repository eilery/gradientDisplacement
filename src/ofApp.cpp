#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowPosition(SCREEN_WIDTH + 1, 0);
    ofSetFullscreen(true);
    
    //----of setups
    ofSetVerticalSync(true);
    ofSetFrameRate(60.0);
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(64);
    ofHideCursor();
    
    //----normalize
    updating = drawing = true;
    gradienting = false;
    switching = false;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    
    //----fbo setups
    gradient.allocate(width, height, GL_RGBA, 4);
    
    mainFbo.allocate(width, height, GL_RGBA, 4);
    postFbo.allocate(width, height, GL_RGBA, 4);
    
    mainEffect.setup(&mainFbo);
    postEffect.setup(&postFbo);
    
    
    //----device setups
    //midiIn.listPorts();
    midiIn.openPort("Launch Control");
    midiIn.ignoreTypes(false);
    midiIn.addListener(this);
    
    //midiOut.listPorts();
    midiOut.openPort("Launch Control");
    updateMidi();
}

//--------------------------------------------------------------
void ofApp::update() {
    aubio.update();
    
    if(updating) {
        if(aubio.beating || drawing) {
            mainFbo.begin();
            gradient.draw(0, 0);
            mainFbo.end();
        }
        mainEffect.updateFx();
        
        postFbo.begin();
        mainFbo.draw(0, 0);
        postFbo.end();
        postEffect.updateFx();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    postFbo.draw(0, 0);
        
    if(!hiding) {
        ofDrawBitmapString("FPS: " + to_string(aubio.getFrameRate()), 0, 10);
        ofDrawBitmapString("BPM: " + to_string(aubio.getBpm()), 0, 25);
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    midiIn.closePort();
    aubio.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key == 13) {
        gradient.saveColor();
    }
    
    if(key == 52) {
        screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        screen.save("screenshot.png");
    }
    
    if(key == 127) {
        gradient.deleteColor();
    }
    
    if(key == 'r') {
        mainEffect.setShader();
        gradient.setShader();
    }
    
    if(key == 'd') drawing =! drawing;
    if(key == 'u') updating =! updating;
    if(key == 'h') hiding =! hiding;
    if(key == 't') mainEffect.toggleFx(POSTEFFECT_TWIST);
    if(key == 'c') mainEffect.toggleFx(POSTEFFECT_CUTUP);
    if(key == 's') mainEffect.toggleFx(POSTEFFECT_SLIT);
    if(key == 'n') postEffect.toggleFx(POSTEFFECT_NOISE);
    if(key == 356 || key == 358) gradient.setMode();
    if(key == 357 || key == 359) gradient.setColorSet();
    
    updateMidi();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    int num = max(msg.control, msg.pitch);
    int value = msg.value;
    
    //cout << "pitch or control: " + to_string(num) << endl;
    //cout << "value: " + to_string(value) << endl;
    
    switch(num) {
        case 11:
            gradient.setValue(BIAS_RED, value);
            break;
        case 21:
            gradient.setValue(BIAS_GREEN, value);
            break;
        case 31:
            gradient.setValue(BIAS_BLUE, value);
            break;
        case 41:
            gradient.setValue(AMPLITUDE_RED, value);
            break;
        case 51:
            gradient.setValue(AMPLITUDE_GREEN, value);
            break;
        case 61:
            gradient.setValue(AMPLITUDE_BLUE, value);
            break;
        case 12:
            gradient.setValue(FREQUENCY_RED, value);
            break;
        case 22:
            gradient.setValue(FREQUENCY_GREEN, value);
            break;
        case 32:
            gradient.setValue(FREQUENCY_BLUE, value);
            break;
        case 42:
            gradient.setValue(PHASE_RED, value);
            break;
        case 52:
            gradient.setValue(PHASE_GREEN, value);
            break;
        case 62:
            gradient.setValue(PHASE_BLUE, value);
            break;
        case 71:
            gradient.setSpeed(value);
            break;
        case 81:
            mainEffect.setValue(value);
            break;
        case 82:
            
            break;
        case 91:
            gradient.setMode();
            break;
        case 92:
            gradient.setColorSet();
            break;
        case 93:
            
            break;
        case 94:
            
            break;
        case 13:
            updating =! updating;
            break;
        case 23:
            drawing =! drawing;
            break;
        case 33:
            break;
        case 43:
            mainEffect.toggleFx(POSTEFFECT_TWIST);
            break;
        case 53:
            mainEffect.toggleFx(POSTEFFECT_CUTUP);
            break;
        case 63:
            mainEffect.toggleFx(POSTEFFECT_SLIT);
            break;
    }
    
    updateMidi();
}

//--------------------------------------------------------------
void ofApp::updateMidi() {
    int green = 40;
    int red = 1;
    
    for(int i = 13; i < 93; i += 10) {
        midiOut.sendNoteOff(1, i);
    }
    
    if(updating) midiOut.sendNoteOn(1, 13, green);
    if(drawing) midiOut.sendNoteOn(1, 23, green);

    if(mainEffect.getFx(POSTEFFECT_TWIST)) {
        midiOut.sendNoteOn(1, 43, green);
    }
    if(mainEffect.getFx(POSTEFFECT_CUTUP)) {
        midiOut.sendNoteOn(1, 53, green);
    }
    if(mainEffect.getFx(POSTEFFECT_SLIT)) {
        midiOut.sendNoteOn(1, 63, green);
    }
}