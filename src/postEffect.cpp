#include "postEffect.h"

postEffect::postEffect() {
    setShader();
    value = 127.0;
}

void postEffect::setup(ofFbo *_fbo) {
    fbo = _fbo;
    brushFbo = maskFbo = NULL;
    noising = false;
    size.set(fbo -> getWidth(), fbo -> getHeight());
    fxFbo.allocate(size.x, size.y);
}

void postEffect::setup(ofFbo *_fbo, ofFbo *_brushFbo, ofFbo *_maskFbo) {
    fbo = _fbo;
    brushFbo = _brushFbo;
    maskFbo = _maskFbo;
    size.set(fbo -> getWidth(), fbo -> getHeight());
    fxFbo.allocate(size.x, size.y);
}

void postEffect::setValue(float _value) {
    value = _value;
}

void postEffect::setShader() {
    shader[0].load("shader/noise");
    shader[1].load("shader/cutup");
    shader[2].load("shader/twist");
    shader[3].load("shader/slit");
}

void postEffect::setFx(postEffectType type, bool enabled) {
    shading[type] = enabled;
}

void postEffect::toggleFx(postEffectType type) {
    shading[type] ^= true;
}

bool postEffect::getFx(postEffectType type) {
    return shading[type];
}

void postEffect::updateFx(){
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //ofSetColor(255);
    
    rand[0] = ofRandom(-1.0, 1.0);
    
    if (ofGetFrameNum() % (int)ofRandom(4, 15) == 0){
        rand[1] = ofRandom(0, 1.0);
        rand[2] = ofRandom(0, 10.0);
        rand[3] = ofRandom(0, 100.0);
        rand[4] = ofRandom(0, 1000.0);
    }
    
    for(int i = 0; i < EFFECT_NUM; i++) {
        if(shading[i]) {
            shader[i].begin();
            shader[i].setUniformTexture("image", *fbo, 0);
            
            shader[i].setUniform2f("resolution", size);
            shader[i].setUniform1f("rand", rand[0]);
            shader[i].setUniform1f("rand1", rand[1]);
            shader[i].setUniform1f("rand2", rand[2]);
            shader[i].setUniform1f("rand3", rand[3]);
            shader[i].setUniform1f("rand4", rand[4]);
            shader[i].setUniform1f("value", value);
            shader[i].setUniform1f("time", ofGetElapsedTimef());
            
            fxFbo.begin();
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ofDrawRectangle(0, 0, size.x, size.y);
            fxFbo.end();
            shader[i].end();
            
            fbo -> begin();
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            fxFbo.draw(0, 0, size.x, size.y);
            fbo -> end();
        }
    }
}
