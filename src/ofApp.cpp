#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    setupMatrix();
    
    dist = ofPoint(0, 0);
    attraction = ofPoint(0, 0);
    
    limit = 0.01;
    showGui = false;
    
    gui.setup();
    gui.setName("PROPERTIES");
    
    gui.add(stiffness.set("stiffness", 0.265, 0, 1));
    gui.add(friction.set("friction", 0.98, 0, 1));
    gui.add(damping.set("damping", 0.125, 0, 1));
    gui.add(mass.set("mass", 5, 0, 20));
//    gui.add(stiffness.set("stiffness", 0.345, 0, 1));
//    gui.add(friction.set("friction", 0.98, 0, 1));
//    gui.add(damping.set("damping", 0.195, 0, 1));
//    gui.add(mass.set("mass", 5, 0, 20));
    
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

void ofApp::setupMatrix() {
    float ballRadius = 17;
    int nbX = ofGetWidth() / (ballRadius * 2) + 1;
    int nbY = ofGetHeight() / (ballRadius * 2) + 1;
    
    if (balls.size() != 0) {
        balls.clear();
    }
    
    for (int x = 0; x < nbX; x++) {
        for (int y = 0; y < nbY; y++) {
            balls.push_back(ball());
            //balls.back().setup((x * ballRadius * 2) + ballRadius, (y * ballRadius * 2) + ballRadius, ballRadius);
            balls.back().setup(x * ballRadius * 2, y * ballRadius * 2, ballRadius);
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
