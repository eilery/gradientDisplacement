#include "aubioSync.h"

aubioSync::aubioSync() {
    bpm = 60.0;
    gotBeat = gotOnset = true;
    
    beat.setup();
    ofAddListener(beat.gotBeat, this, &aubioSync::beatEvent);
    
    onset.setup();
    ofAddListener(onset.gotOnset, this, &aubioSync::onsetEvent);
    
    //pitch.setup();
    //bands.setup();
    
    soundStream.setup(this, 2, 2, 44100, 256, 4);
}

//--------------------------------------------------------------
void aubioSync::update() {
    beating = false;
    frameRate = ofGetFrameRate();
    threshold = frameRate * 60.0 / bpm;
    
    if(threshold < frameCount) {
        frameCount -= threshold;
        //cout << "Beat!" << endl;
        beating = true;
    }

    gotBeat = gotOnset = false;
    frameCount++;
}

void aubioSync::exit() {
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void aubioSync::beatEvent(float &time) {
    gotBeat = true;
    bpm = beat.bpm;
}

//--------------------------------------------------------------
void aubioSync::onsetEvent(float &time) {
    gotOnset = true;
}

void aubioSync::audioIn(float *input, int bufferSize, int nChannels) {
    beat.audioIn(input, bufferSize, nChannels);
}

void aubioSync::audioOut() {
    
}

//--------------------------------------------------------------
float aubioSync::getFrameRate() {
    return frameRate;
}

//--------------------------------------------------------------
float aubioSync::getBpm() {
    return bpm;
}