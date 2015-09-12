//
//  shape.h
//  springBounce
//
//  Created by Martial on 10/09/2015.
//
//

#ifndef __springBounce__shape__
#define __springBounce__shape__

#include <ofMain.h>

class shape : public ofMesh {
public:
    shape();
    ~shape();
    
    void setup(float x, float y, float r, ofColor c);
    void update();
    bool inArea(float x, float y);

    float areaRadius;
    ofColor color;
    float radius;
    int resolution;
    ofPoint pin;
    ofPoint position;
    
    // TO CHANGE ???
    ofPoint dist;
    ofPoint velocity;
    
    ofPolyline poly;
};





#endif /* defined(__springBounce__shape__) */
