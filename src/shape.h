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

class shape {
public:
    shape();
    ~shape();
    
    void setup(float x, float y, float r, ofColor c);

    inline void update(){
        // Compute shape position
    	const float limit = 0.05;
        ofVec3f dist = pin - position;
        ofVec3f attraction = ((dist * 0.265) - (0.125 * dist))/5.0;
        velocity = (velocity + attraction) * 0.98;
        position = position + velocity;

        auto lensq = dist.lengthSquared();
        if(lensq < limit*limit) position = pin;
    }
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
    bool pinned;
};





#endif /* defined(__springBounce__shape__) */
