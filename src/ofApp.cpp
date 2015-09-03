#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    ballRadius = 12;
    nbX = ofGetWidth() / (ballRadius * 2) + 1;
    nbY = ofGetHeight() / (ballRadius * 2) + 1;
    
    // limit distance to a circle to fire interaction
    limit = 0.01;
    
    image.loadImage("pattern.png");
    image.resize(nbX, nbY);
    
    setupMatrix();
    
    // Physics
    dist = ofPoint(0, 0);
    attraction = ofPoint(0, 0);
    
    bShowGui = false;
    
    // GUI
    
    gui.setup();
    gui.setName("PROPERTIES");
    
    gui.add(stiffness.set("stiffness", 0.265, 0, 1)); // 0.345
    gui.add(friction.set("friction", 0.98, 0, 1)); // 0.98
    gui.add(damping.set("damping", 0.125, 0, 1)); // 0.195
    gui.add(mass.set("mass", 5, 0, 20)); // 5
    gui.add(bOsc.set("OSC", false));
    gui.add(bKinect.set("Kinect", false));
    
    gui.loadFromFile("settings.xml");
    
    // OSC
    receiver.setup(3333);
    
    // KINECT
    kinectPoint.set(-10, -10);
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
    
    // If OSC Enabled
    if (bOsc) {
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(&m);
            
            // check for mouse x moved message
            if(m.getAddress() == "/kinect/x"){
                kinectPoint.x = m.getArgAsFloat(0);
            }
            // check for mouse y moved message
            else if(m.getAddress() == "/kinect/y"){
                kinectPoint.y = m.getArgAsFloat(0);
            }
            // check if blob is detected by kinect
            else if(m.getAddress() == "/kinect/detected"){
                bBlobDetected = m.getArgAsInt32(0);
            }
        }
    }
    
    // If Kinect Enabled
    if (bKinect) {
        if (bBlobDetected) {
            
            for (int i = 0; i < balls.size(); i++) {
                float x = kinectPoint.x * ofGetWidth();
                float y = kinectPoint.y * ofGetHeight();
                
                if (balls[i].inArea(x, y)) {
                    balls[i].position.set(x, y);
                }
            }
        }
        else
        {
            kinectPoint.set(-10, -10);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);

    for (int i = 0; i < balls.size(); i++) {
        balls[i].draw();
    }
    
    if (bShowGui) {
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
        bShowGui = !bShowGui;
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
