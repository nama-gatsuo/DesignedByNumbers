#ifndef LabelSystem_hpp
#define LabelSystem_hpp

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class LabelSystem {
public:
    LabelSystem();
    void update(ofCamera * cam);
    void draw(float * t);
    void drawLabel(ofVec3f * p, string & label, float t);
    
    vector<string> cl0;
    vector<float> ct0;
    vector<vector<string>> cl1;
    vector<vector<float>> ct1;
    vector<vector<string>> rl;
    
private:
    ofxTrueTypeFontUC font;
    ofNode node;
    ofMatrix4x4 mat;
};
#endif /* LabelSystem_hpp */
