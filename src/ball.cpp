//
//  ball.cpp
//  testAttraction
//
//  Created by Martial on 01/08/2015.
//
//

#include "ball.h"

void ball::setup(float x, float y, float r) {
    pin = ofPoint(x, y);
    position = pin;
    radius = r;
    velocity = ofPoint(0, 0);
    areaRadius = 25;
    dist = ofPoint(0,0);
    //color.set(ofRandom(16), ofRandom(16), ofRandom(16));
    //color.set(0, 0, 0);
}

void ball::update() {
    dist = pin - position;
}

void ball::draw() {
    
    ofPushMatrix();
    ofColor c = ofColor(ofMap(dist.x + dist.y, -10, 10, 40, 200, true));
    // formula for color SCREEN blend mode
    ofSetColor(ofColor(255) - (((ofColor(255) - c)*(ofColor(255) - color))/ofColor(255)));
    //ofSetColor(color + c);
    ofCircle(position, radius);
    ofPopMatrix();
}

bool ball::inArea(float x, float y) {
    if (ofDist(x, y, position.x, position.y) < areaRadius) {
        return true;
    }
    else {
        return false;
    }
}