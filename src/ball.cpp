//
//  ball.cpp
//  testAttraction
//
//  Created by Martial on 01/08/2015.
//
//

#include "ball.h"

void ball::setup(float x, float y, float r, ofColor col) {
    pin = ofPoint(x, y);
    position = pin;
    radius = r;
    velocity = ofPoint(0, 0);
    areaRadius = 25;
    dist = ofPoint(0,0);
    color.set(col);
}

void ball::update() {
    dist = pin - position;
}

void ball::draw(float contrast) {
    
    ofPushMatrix();
    ofColor c = ofColor(ofMap(dist.x + dist.y, -10, 10, 20, 220, true));
    
    // formula for color SCREEN blend mode
    ofSetColor(ofColor(255) - (((ofColor(255) - c)*(ofColor(255) - color))/ofColor(contrast)));
    
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