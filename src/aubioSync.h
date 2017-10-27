#pragma once

#include "ofMain.h"
#include "ofxAubio.h"

class aubioSync : ofBaseApp {
    
public:
    aubioSync();
    void update();
    void exit();
    void beatEvent(float &time);
    void onsetEvent(float &time);
    
    float getFrameRate();
    float getBpm();
        
    void audioIn(float *input, int bufferSize, int nChannels);
    void audioOut();

    bool beating;
    
private:
    ofSoundStream soundStream;
    
    float frameRate, frameCount, bpm, threshold;
    
    ofxAubioOnset onset;
    ofxAubioBeat beat;
    //ofxAubioPitch pitch;
    //ofxAubioMelBands bands;
    
    bool gotBeat, gotOnset;
};