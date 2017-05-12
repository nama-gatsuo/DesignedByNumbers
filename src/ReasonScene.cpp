#include "ReasonScene.hpp"

void ReasonScene::setup(){
    
    shader.load("shader/reason");
    
    total.setup();
    
    vbo.setMode(OF_PRIMITIVE_POINTS);
    
    if (json.open("json/reason_gen_age.json")) {
        
        fbo.allocate(256, 128, GL_RGBA32F);
        
        vector<float> a(256 * 128 * 4);
        
        int n0 = json["label"]["column"].size(),
        n1, n2 = 2, n3 = 9;
        
        EDGE_NUM = n0;
        EXP_NUM = 4;
        
        float index = 0;
        float t0, t1, t2, t3;
        int wh = 0;
        
        int ttl = 52;
        int tmp = 0;
        
        
        // attr 1
        for (int i0 = 0; i0 < n0; i0++) {
            
            n1 = json["label"]["column"][i0]["child"].size();
            tmp += n1;
            
            float ta = 1.0 / ttl * n1;
            t0 = 1.0 / ttl * (tmp - n1 * 0.5);
            
            tcp.push_back(ofVec3f(cos(t0 * TWO_PI),0,sin(t0 * TWO_PI)) * 330);
            system.ct0.push_back(t0 * TWO_PI);
            system.cl0.push_back(json["label"]["column"][i0]["parent"].asString());
            system.ct1.push_back(vector<float>());
            system.cl1.push_back(vector<string>());
            
            // attr 2
            for (int i1 = 0; i1 < n1; i1++) {
                
                t1 = ta / n1 * (i1 - n1 * 0.5);
                system.ct1[i0].push_back(t1 * TWO_PI);
                system.cl1[i0].push_back(json["label"]["column"][i0]["child"][i1].asString());
                
                // gender
                for (int i2 = 0; i2 < n2; i2++) {
                    
                    float sign = pow(-1.0, i2);
                    t2 = 1.0 * sign;
                    
                    // age
                    for (int i3 = 0; i3 < n3; i3++) {
                        
                        int num = json["data"][i0][i1][i2][i3].asInt();
                        t3 = sign * 1.1 / 9 * (i3 - 3.0);
                        
                        ofFloatColor c;
                        c.setHsb(0.5 + 0.4 * i2 + 0.02 * (9 - i3), 0.6, 0.8);
                        
                        for (int i = 0; i < num; i++) {
                            a[index++] = t0;
                            a[index++] = t1;
                            a[index++] = t2;
                            a[index++] = t3;
                            
                            ofVec3f v = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)).normalize();
                            v *= ofRandom(sqrt(num * 0.2));
                            
                            float s = 0.5 + wh % 256;
                            float t = 0.5 + floor(wh / 256);
                            
                            vbo.addVertex(v);
                            vbo.addTexCoord(ofVec2f(s, t));
                            vbo.addColor(c);
                            
                            wh++;
                        }
                    
                    }
                }
            }
        }
        
        
        fbo.getTexture().loadData(a.data(), 256, 128, GL_RGBA);
        
        
        system.rl.push_back(vector<string>());
        system.rl.push_back(vector<string>());
        
        for (int i = 0; i < 2; i++) {
            system.rl[0].push_back(json["label"]["row"][0][i].asString());
        }
        for (int i = 0; i < 9; i++) {
            system.rl[1].push_back(json["label"]["row"][1][i].asString());
        }
    }
    
    cp.to(tcp[EDGE_CURRENT]);
    cam.setPosition(cp);
    
    size.to(pow((5.0 - EXP_CURRENT) * 0.5, 2.0));
}

void ReasonScene::update() {
    
    cp.update();
    cam.setPosition(cp.x, 30 * sin(ofGetElapsedTimef()/3), cp.z);
    cam.lookAt(ofVec3f(.0));
    
    for (int i = 0; i < 4; i++) {
        tt[i].update();
        t[i] = tt[i].getValue();
    }
    
    size.update();
    
    system.update(&cam);
    
}

void ReasonScene::draw() {
    cam.begin();
    shader.begin();
    shader.setUniformTexture("tex", fbo.getTexture(), 0);
    shader.setUniform1fv("t", t, 4);
    shader.setUniform1f("time", ofGetElapsedTimef()/2);
    shader.setUniform1f("size", size.getValue());
    
    vbo.draw();
    shader.end();
    
    system.draw(t);
    
    total.draw();
    
    ofNoFill();
    ofSetColor(32);
    ofDrawSphere(0, 0, 0, 400);
    ofFill();
    
    cam.end();
}

void ReasonScene::keyPressed(int key) {
    
    if (key == OF_KEY_LEFT) {
        EDGE_CURRENT++;
        if (EDGE_CURRENT == EDGE_NUM) EDGE_CURRENT = 0;
        cp.to(tcp[EDGE_CURRENT]);
    }
    else if (key == OF_KEY_RIGHT) {
        EDGE_CURRENT--;
        if (EDGE_CURRENT == -1) EDGE_CURRENT = EDGE_NUM - 1;
        cp.to(tcp[EDGE_CURRENT]);
    }
    
    if (key == ' ') {
        
        if (EXP_VEC > 0) expand();
        else shrink();
        
        EXP_CURRENT += EXP_VEC;
        
        if (EXP_CURRENT == 0) EXP_VEC = 1;
        else if (EXP_CURRENT == EXP_NUM) EXP_VEC = -1;
        
        
    }
    
}


void ReasonScene::expand() {
    tt[EXP_CURRENT].to(1.0);
    size.to(pow((4.0 - EXP_CURRENT) * 0.8, 1.5));
}

void ReasonScene::shrink() {
    tt[EXP_CURRENT-1].to(0.0);
    size.to(pow((6.0 - EXP_CURRENT) * 0.8, 1.5));
}
