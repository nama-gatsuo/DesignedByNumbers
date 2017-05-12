#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    boost::shared_ptr<VisualizeScene> sp(new ReasonScene());
    sp->setup();
    scenes.push_back(sp);
    
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    //fbo.getTexture().getTextureData().bFlipTexture = true;
    server.setName("dataVis");
}

//--------------------------------------------------------------
void ofApp::update(){
    scenes[mode]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    
    fbo.begin();
    ofClear(0);
    scenes[mode]->draw();
    fbo.end();
    
    ofDisableBlendMode();
    
    fbo.draw(0,0);
    
    server.publishFBO(&fbo);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    scenes[mode]->keyPressed(key);
}

void ofApp::windowResized(int w, int h){
    fbo.clear();
    fbo.allocate(w, h);
}
