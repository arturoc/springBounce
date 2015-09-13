//
//  shape.cpp
//  springBounce
//
//  Created by Martial on 10/09/2015.
//
//

#include "shape.h"


shape::shape() {

}

shape::~shape() {

}

void shape::setup(float x, float y, float r, ofColor c) {
    pin.set(x, y);
    position.set(pin);
    radius = r;
    color = c;
    dist = ofPoint(0, 0);
    areaRadius = 25;
    pinned = true;
}

bool shape::inArea(float x, float y) {
    if (ofDist(x, y, position.x, position.y) < areaRadius) {
        return true;
    }
    else {
        return false;
    }
}
