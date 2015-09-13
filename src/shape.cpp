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
    
}

void shape::update() {
    
    //dist = pin - position;
    
    poly.clear();
    this->clear();
    
    poly.arc(0, 0, radius, radius, 0, 360);
    
    for (int i = 0; i < poly.getVertices().size() - 1; i++) {
        this->addVertex(poly[i]);
        this->addColor(color);
        this->addVertex(poly[i + 1]);
        this->addColor(color);
        this->addVertex(ofPoint(0, 0));
        this->addColor(color);
    }
}

bool shape::inArea(float x, float y) {
    if (ofDist(x, y, position.x, position.y) < areaRadius) {
        return true;
    }
    else {
        return false;
    }
}
