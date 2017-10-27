#pragma once

#include "ofMain.h"

#define EFFECT_NUM 4

enum postEffectType {
    POSTEFFECT_NOISE,
    POSTEFFECT_CUTUP,
    POSTEFFECT_TWIST,
    POSTEFFECT_SLIT
};

class postEffect {
public:
    postEffect();
    
    void setup(ofFbo *_fbo);
    void setup(ofFbo *_fbo, bool _noising);
    void setup(ofFbo *_fbo, ofFbo *_brushFbo, ofFbo *_maskFbo);
    void setShader();
    void setValue(float value);
    void setFx(postEffectType type, bool enabled);
    void toggleFx(postEffectType type);
    bool getFx(postEffectType type);
    void updateFx();
    
protected:
    bool shading[EFFECT_NUM];
    ofShader shader[EFFECT_NUM];
    ofShader brush;
    ofFbo* fbo;
    ofFbo* brushFbo;
    ofFbo* maskFbo;
    ofFbo fxFbo;
    ofVec2f size;
    float rand[5];
    float value;
    
    bool noising;
};