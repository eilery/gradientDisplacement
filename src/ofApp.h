#pragma once

#include "ofMain.h"
#include "ofSettings.h"

#include "ofxMidi.h"

#include "postEffect.h"
#include "aubioSync.h"
#include "cosineGradient.h"

class ofApp : public ofBaseApp, public ofxMidiListener {
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void newMidiMessage(ofxMidiMessage &msg);
    void updateMidi();
    
    aubioSync aubio;
    cosineGradient gradient;
    postEffect mainEffect, postEffect;
    
    ofxMidiIn midiIn;
    ofxMidiOut midiOut;
    ofxMidiMessage msg;
    
    ofFbo mainFbo, postFbo;
    
    ofPixels pixels;
    ofImage image;
    ofImage screen;
    
    bool shading, drawing, updating;
    bool gradienting;
    bool hiding, switching;
    bool saving, pasting;
        
    int width, height;
};

