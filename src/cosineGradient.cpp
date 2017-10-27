#include "cosineGradient.h"

parameter4c3f::parameter4c3f() {
    bias = ofVec3f(0.5, 0.5, 0.5);
    amp = ofVec3f(0.5, 0.5, 0.5);
    freq = ofVec3f(1.5, 1.5, 1.5);
    phase = ofVec3f(0.5, 0.5, 0.5);
}

parameter4c3f::parameter4c3f(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
    bias = a;
    amp = b;
    freq = c;
    phase = d;
}

cosineGradient::cosineGradient() {
    mode = LINEAR_GRADIENT;
    xml.loadFile("colorsets.xml");
    xmlNum = xml.getNumTags("COLOR");
    
    for(int i = 0, l = xmlNum; i < l; i++) {
        xml.pushTag("COLOR", i);
            xml.pushTag("BIAS");
                colorSet.bias.x = xml.getValue("R", 0.5);
                colorSet.bias.y = xml.getValue("G", 0.5);
                colorSet.bias.z = xml.getValue("B", 0.5);
            xml.popTag();
            xml.pushTag("AMPLITUDE");
                colorSet.amp.x = xml.getValue("R", 0.5);
                colorSet.amp.y = xml.getValue("G", 0.5);
                colorSet.amp.z = xml.getValue("B", 0.5);
            xml.popTag();
            xml.pushTag("FREQUENCY");
                colorSet.freq.x = xml.getValue("R", 0.5);
                colorSet.freq.y = xml.getValue("G", 0.5);
                colorSet.freq.z = xml.getValue("B", 0.5);
            xml.popTag();
            xml.pushTag("PHASE");
                colorSet.phase.x = xml.getValue("R", 0.5);
                colorSet.phase.y = xml.getValue("G", 0.5);
                colorSet.phase.z = xml.getValue("B", 0.5);
            xml.popTag();
        xml.popTag();
        
        colorSets.push_back(colorSet);
    }
    
    colorSet = originalColorSet;
    
    speed = 0.5;
    noising = true;
    setShader();
}

void cosineGradient::setShader() {
    shader[0].load("shader/linear");
    shader[1].load("shader/radial");
    shader[2].load("shader/polar");
    noise.load("shader/noise");
}

void cosineGradient::setMode() {
    if(mode == LINEAR_GRADIENT) {
        mode = RADIAL_GRADIENT;
    } else if(mode == RADIAL_GRADIENT) {
        mode = POLAR_GRADIENT;
    } else {
        mode = LINEAR_GRADIENT;
    }
}

void cosineGradient::setSpeed(int value) {
    float s = ofMap(value, 0, 127, 0, 1.0);
    speed = s;
}

void cosineGradient::allocate(int width, int height, int internalformat, int numSamples) {
    size.x = width;
    size.y = height;
    r = ofRandom(0, 1.0);
    
    fbo.allocate(size.x, size.y, internalformat, numSamples);
}

void cosineGradient::draw(int x, int y) {
    shader[mode].begin();
    shader[mode].setUniform3f("a", colorSet.bias);
    shader[mode].setUniform3f("b", colorSet.amp);
    shader[mode].setUniform3f("c", colorSet.freq);
    shader[mode].setUniform3f("d", colorSet.phase);
    shader[mode].setUniform2f("resolution", size);
    shader[mode].setUniform1f("time", ofGetElapsedTimef());
    shader[mode].setUniform1f("speed", speed);
    fbo.begin();
    ofDrawRectangle(0, 0, size.x, size.y);
    fbo.end();
    shader[mode].end();
    
    if(noising) {
        noise.begin();
        noise.setUniformTexture("image", fbo, 0);
        noise.setUniform1f("rand", r);
        fbo.begin();
        ofDrawRectangle(0, 0, size.x, size.y);
        fbo.end();
        noise.end();
    }
    
    fbo.draw(x, y);
}

void cosineGradient::setValue(parameterName parameter, int value) {
    float v = ofMap(value, 0, 127, 0, 1.0);
    
    colorSet = originalColorSet;
    
    if(parameter == BIAS_RED) {
        colorSet.bias.x = v;
        originalColorSet.bias.x = colorSet.bias.x;
    } else if(parameter == BIAS_GREEN) {
        colorSet.bias.y = v;
        originalColorSet.bias.y = colorSet.bias.y;
    } else if(parameter == BIAS_BLUE) {
        colorSet.bias.z = v;
        originalColorSet.bias.z = colorSet.bias.z;
    } else if(parameter == AMPLITUDE_RED) {
        colorSet.amp.x = v;
        originalColorSet.amp.x = colorSet.amp.x;
    } else if(parameter == AMPLITUDE_GREEN) {
        colorSet.amp.y = v;
        originalColorSet.amp.y = colorSet.amp.y;
    } else if(parameter == AMPLITUDE_BLUE) {
        colorSet.amp.z = v;
        originalColorSet.amp.z = colorSet.amp.z;
    } else if(parameter == FREQUENCY_RED) {
        colorSet.freq.x = floor(v * 6.0) / 2.0;
        originalColorSet.freq.x = colorSet.freq.x;
    } else if(parameter == FREQUENCY_GREEN) {
        colorSet.freq.y = floor(v * 6.0) / 2.0;
        originalColorSet.freq.y = colorSet.freq.y;
    } else if(parameter == FREQUENCY_BLUE) {
        colorSet.freq.z = floor(v * 6.0) / 2.0;
        originalColorSet.freq.z = colorSet.freq.z;
    } else if(parameter == PHASE_RED) {
        colorSet.phase.x = v;
        originalColorSet.phase.x = colorSet.phase.x;
    } else if(parameter == PHASE_GREEN) {
        colorSet.phase.y = v;
        originalColorSet.phase.y = colorSet.phase.y;
    } else if(parameter == PHASE_BLUE) {
        colorSet.phase.z = v;
        originalColorSet.phase.z = colorSet.phase.z;
    }
    
    xmlNum = colorSets.size();
}

void cosineGradient::setColorSet() {
    if(xmlNum < colorSets.size() - 1) {
        xmlNum++;
        colorSet = colorSets[xmlNum];
    } else {
        xmlNum = 0;
        colorSet = colorSets[0];
    }
}

void cosineGradient::saveColor() {
    xmlNum = colorSets.size();
    
    xml.addTag("COLOR");
    xml.pushTag("COLOR", xmlNum);
        xml.addTag("BIAS");
        xml.pushTag("BIAS");
            xml.setValue("R:", colorSet.bias.x);
            xml.setValue("G:", colorSet.bias.y);
            xml.setValue("B:", colorSet.bias.z);
        xml.popTag();
        xml.addTag("AMPLITUDE");
        xml.pushTag("AMPLITUDE");
            xml.setValue("R:", colorSet.amp.x);
            xml.setValue("G:", colorSet.amp.y);
            xml.setValue("B:", colorSet.amp.z);
        xml.popTag();
        xml.addTag("FREQUENCY");
        xml.pushTag("FREQUENCY");
            xml.setValue("R:", colorSet.freq.x);
            xml.setValue("G:", colorSet.freq.y);
            xml.setValue("B:", colorSet.freq.z);
        xml.popTag();
        xml.addTag("PHASE");
        xml.pushTag("PHASE");
            xml.setValue("R:", colorSet.phase.x);
            xml.setValue("G:", colorSet.phase.y);
            xml.setValue("B:", colorSet.phase.z);
        xml.popTag();
    xml.popTag();
    
    colorSets.push_back(colorSet);
    
    xml.saveFile("colorsets.xml");
}

void cosineGradient::deleteColor() {
    if(1 < colorSets.size() && xmlNum < colorSets.size()) {
        xml.removeTag("COLOR", xmlNum);
        colorSets.erase(colorSets.begin() + xmlNum);
        xmlNum--;
        if(xmlNum < 0) xmlNum = colorSets.size() - 1;
        colorSet = colorSets[xmlNum];
        
        xml.saveFile("colorsets.xml");
    }
}