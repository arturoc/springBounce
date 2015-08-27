//
//  ball.h
//  testAttraction
//
//  Created by Martial on 01/08/2015.
//
//

#ifndef __testAttraction__ball__
#define __testAttraction__ball__

#include <ofMain.h>

class ball {
public:
    
    void setup(float x, float y, float r);
    void update();
    void draw();
    
    bool inArea(float x, float y);
    
    ofPoint position;
    float radius;
    
    float areaRadius;
    
    ofPoint velocity;
    
    ofPoint pin;
    
    ofPoint dist;
   
    ofColor color;
    
};


#endif /* defined(__testAttraction__ball__) */
