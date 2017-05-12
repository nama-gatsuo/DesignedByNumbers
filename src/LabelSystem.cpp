#include "LabelSystem.hpp"

LabelSystem::LabelSystem(){
    font.load("font/hiragino.ttc", 16, true, true);
}

void LabelSystem::update(ofCamera * cam){
    
    node.lookAt(- cam->getPosition(), ofVec3f(0, 1.0, 0));
    mat = node.getGlobalTransformMatrix();
    mat.glRotate(180, 1, 0, 0);
}

void LabelSystem::draw(float * t){
    
    ofPushStyle();
    
    ofVec3f p0, p1, p2, p3;
    
    for (int i = 0; i < cl0.size(); i++) {
        
        p0 = ofVec3f(cos(ct0[i]), 0, sin(ct0[i]));
        p0 *= 180.0 * t[0];
        
        ofPushMatrix();
        ofTranslate(p0.x * 1.1, p0.y * 1.1, p0.z * 1.1);
        ofScale(0.25, 0.25, 0.25);
        ofMultMatrix(mat);
        
        ofSetColor(255, t[0] * 255);
        font.drawStringAsShapes(cl0[i], 0, 0);
        ofPopMatrix();
        
        
        ofDrawLine(ofVec3f(0,0,0), p0);
        
        // sub category
        for (int j = 0; j < cl1[i].size(); j++) {
            
            p1 = ofVec3f(cos(ct0[i] + ct1[i][j] * t[1]), 0, sin(ct0[i] + ct1[i][j] * t[1]));
            p1 *= 180.0;
            
            ofPushMatrix();
            ofTranslate(p1.x, p1.y+10.0, p1.z);
            ofScale(0.15, 0.15, 0.15);
            ofMultMatrix(mat);
            ofRotateZ(60);
            
            ofSetColor(255, t[1] * 255);
            font.drawStringAsShapes(cl1[i][j], 0, 0);
            ofPopMatrix();
            
        }
        
        // gender
        for (int j = 0; j < 2; j++) {
            
            float sign = pow(-1.0, j);
            
            p2 = ofVec3f(cos(ct0[i])*180, sign * 40.0 * t[2], sin(ct0[i])*180);
            
            ofPushMatrix();
            ofTranslate(p2.x * 1.1, p2.y * 1.5, p2.z * 1.1);
            ofScale(0.2, 0.2, 0.2);
            ofMultMatrix(mat);
            
            ofSetColor(255, t[2] * 255);
            font.drawStringAsShapes(rl[0][j], 0, 0);
            ofPopMatrix();
            
            ofDrawLine(p0, p2);
            
            for (int k = 0; k < 9; k++) {
                
                p3 = p2;
                p3.y += sign * 88.0 * t[3] / 9 * (k - 3.0);
                
                ofPushMatrix();
                ofTranslate(p3.x, p3.y, p3.z);
                ofScale(0.15, 0.15, 0.15);
                ofMultMatrix(mat);
                
                ofSetColor(255, t[3] * 255);
                font.drawStringAsShapes(rl[1][k], 0, 0);
                ofPopMatrix();
                
            }
            
            ofDrawLine(p0, p3);
            
        }
        
    }
    
    ofPopStyle();
    
}

void LabelSystem::drawLabel(ofVec3f * p, string & label, float t) {
    
    ofPushMatrix();
    ofTranslate(p->x, p->y, p->z);
    ofScale(0.1, 0.1, 0.1);
    ofMultMatrix(mat);
    
    ofSetColor(255, t * 255);
    font.drawStringAsShapes(label, 0, 0);
    ofPopMatrix();

}
