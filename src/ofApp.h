#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

#include "VisualizeScene.hpp"
#include "ReasonScene.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
        void windowResized(int w, int h);
    
    int mode = 0;
    vector<boost::shared_ptr<VisualizeScene>> scenes;
    
    ofxSyphonServer server;
    ofFbo fbo;
};
