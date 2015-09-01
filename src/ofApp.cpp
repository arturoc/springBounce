#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    ballRadius = 10;
    nbX = ofGetWidth() / (ballRadius * 2) + 1;
    nbY = ofGetHeight() / (ballRadius * 2) + 1;
    
    image.loadImage("pattern.png");
    image.resize(nbX, nbY);
    
    setupMatrix();
    
    dist = ofPoint(0, 0);
    attraction = ofPoint(0, 0);
    
    limit = 0.01;
    showGui = false;
    
    gui.setup();
    gui.setName("PROPERTIES");
    
    gui.add(stiffness.set("stiffness", 0.265, 0, 1)); // 0.345
    gui.add(friction.set("friction", 0.98, 0, 1)); // 0.98
    gui.add(damping.set("damping", 0.125, 0, 1)); // 0.195
    gui.add(mass.set("mass", 5, 0, 20)); // 5
    
    receiver.setup(3333);
    
    kinectPoint.set(0, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < balls.size(); i++) {
        
        dist = balls[i].pin - balls[i].position;
        attraction = ((dist * stiffness) - (damping * dist))/mass;
        balls[i].velocity = (balls[i].velocity + attraction) * friction;
        balls[i].position = balls[i].position + balls[i].velocity;
        
        if (dist.length() < limit) {
            balls[i].position = balls[i].pin;
        }
        balls[i].update();
    }
    
    if (bOsc) {
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(&m);
            
            // check for mouse moved message
            if(m.getAddress() == "/kinect/x"){
                kinectPoint.x = m.getArgAsFloat(0);
            }
            // check for mouse button message
            else if(m.getAddress() == "/kinect/y"){
                kinectPoint.y = m.getArgAsFloat(0);
            }
        }
    }
    
    if (bKinect) {
        for (int i = 0; i < balls.size(); i++) {
            float x = kinectPoint.x * ofGetWidth();
            float y = kinectPoint.y * ofGetHeight();
            
            if (balls[i].inArea(x, y)) {
                balls[i].position.set(x, y);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    for (int i = 0; i < balls.size(); i++) {
        balls[i].draw();
    }
    
    if (showGui) {
        gui.draw();
    }
}

//--------------------------------------------------------------

void ofApp::setupMatrix() {
    if (balls.size() != 0) {
        balls.clear();
    }
    
    for (int y = 0; y < nbY; y++) {
        for (int x = 0; x < nbX; x++) {
            balls.push_back(ball());
            float posx = x * ballRadius * 2;
            float posy = y * ballRadius * 2;
            ofColor c = image.getColor(x, y);
            balls.back().setup(posx , posy, ballRadius, c);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_TAB) {
        showGui = !showGui;
    }
    if (key == ' ') {
        ofImage scr;
        scr.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        scr.saveImage("screenshot.png");
    }
    if (key == 'f') {
        ofToggleFullscreen();
        setupMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i].inArea(x, y)) {
            balls[i].position.set(x, y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}
