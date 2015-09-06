#pragma once

#include "ofMain.h"
#include "ball.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
    void setupMatrix();
    
    ofPoint dist;
    ofPoint attraction;
    
    vector<ball> balls;
    
    float limit;
    
    ofxPanel gui;
    
    ofParameter<float> mass;
    ofParameter<float> damping;
    ofParameter<float> stiffness;
    ofParameter<float> friction;
    
    ofParameter<bool> bOsc;
    ofParameter<bool> bKinect;
    
    ofParameter<float> contrast;
    
    ofParameter<float> twinkle;
    ofParameter<bool> bTwinkle;
    
    bool bBlobDetected;
    bool bShowGui;
    
    ofxOscReceiver receiver;
    
    ofPoint kinectPoint;
    
    ofImage image;
    
    int nbX;
    int nbY;
    float ballRadius;
    
};

