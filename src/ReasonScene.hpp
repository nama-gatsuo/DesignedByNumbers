#ifndef AttrScene_hpp
#define AttrScene_hpp

#include "VisualizeScene.hpp"

class TotalParticle {
public:
    void setup(){
        shader.load("shader/sprite");
        
        vbo.setMode(OF_PRIMITIVE_POINTS);
        for (int i = 0; i < totalNum; i++) {
            ofVec3f v = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)).normalize();
            v *= ofRandom(200, 1000);
            
            vbo.addVertex(v);
            vbo.addColor(ofFloatColor(0.2,0.2,0.2, 1.0));
        }
    };
    
    void draw(){
        
        shader.begin();
        shader.setUniform1f("time", ofGetElapsedTimef());
        vbo.draw();
        shader.end();
        
    };
private:
    int totalNum = 1266419;
    ofShader shader;
    ofVboMesh vbo;
};

class ReasonScene : public VisualizeScene {
public:
    virtual void setup() final;
    virtual void update() final;
    virtual void draw() final;
    virtual void keyPressed(int key) final;
    virtual void expand() final;
    virtual void shrink() final;
    
private:
    float t[4];
    SmoothValue tt[4];
    SmoothValue size;
    TotalParticle total;
};

#endif /* AttrScene_hpp */
