#ifndef VisualizeScene_hpp
#define VisualizeScene_hpp

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxJSON.h"
#include "LabelSystem.hpp"
#include "CommonUtil.hpp"

class VisualizeScene {
public:
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void keyPressed(int key){};
    virtual void expand(){};
    virtual void shrink(){};
    
protected:
    ofVboMesh vbo;
    ofFbo fbo;
    ofShader shader;
    
    ofxJSONElement json;
    int EDGE_NUM;
    int EDGE_CURRENT = 0;
    int EXP_NUM;
    int EXP_CURRENT = 0;
    int EXP_VEC = 1;
    ofEasyCam cam;
    vector<ofPoint> tcp;
    SmoothPoint cp;
    LabelSystem system;
};

#endif /* VisualizeScene_hpp */
