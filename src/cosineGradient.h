#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"


enum parameterName {
    BIAS_RED, BIAS_GREEN, BIAS_BLUE,
    AMPLITUDE_RED, AMPLITUDE_GREEN, AMPLITUDE_BLUE,
    FREQUENCY_RED, FREQUENCY_GREEN, FREQUENCY_BLUE,
    PHASE_RED, PHASE_GREEN, PHASE_BLUE
};

enum gradientMode {
    LINEAR_GRADIENT, RADIAL_GRADIENT, POLAR_GRADIENT
};

class parameter4c3f {
public:
    parameter4c3f();
    parameter4c3f(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    ofVec3f bias, amp, freq, phase;
};

class cosineGradient {
public:
    cosineGradient();
    void allocate(int width, int height, int internalformat, int numSamples);
    void setShader();
    void setMode();
    void setSpeed(int value);
    void setValue(parameterName parameter, int value);
    void setColorSet();
    void saveColor();
    void deleteColor();
    void draw(int x, int y);
    
private:
    gradientMode mode;
    
    ofxXmlSettings xml;
    int xmlNum;
    ofFbo fbo;
    ofShader shader[3];
    ofShader noise;
    bool noising;
    
    ofVec2f size;
    float r;
    float speed;
    
    vector<parameter4c3f> colorSets;
    parameter4c3f colorSet, originalColorSet;
};