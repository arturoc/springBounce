#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    float shapeRadius = 17;
    float nbX = ofGetWidth() / (shapeRadius * 2) + 1;
    float nbY = ofGetHeight() / (shapeRadius * 2) + 1;
    
    // limit distance to circle from pin center to consider it still
    limit = 0.05;
    
    // Setup shapes
    if (shapes.size() != 0) {
        shapes.clear();
    }
    
    for (int y = 0; y < nbY; y++) {
        for (int x = 0; x < nbX; x++) {
            shapes.push_back(shape());
            float posx = x * shapeRadius * 2;
            float posy = y * shapeRadius * 2;
            //ofColor c = image.getColor(x, y);
            ofColor c = ofColor(ofRandom(130, 180));
            shapes.back().setup(posx , posy, shapeRadius, c);
        }
    }
    
    // Physics
    dist = ofPoint(0, 0);
    attraction = ofPoint(0, 0);
    
    vboMesh.clear();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vboMesh.clear();
    
    for (int i = 0; i < shapes.size(); i++) {
        
        // Compute shape position
        dist = shapes[i].pin - shapes[i].position;
        attraction = ((dist * 0.265) - (0.125 * dist))/5;
        shapes[i].velocity = (shapes[i].velocity + attraction) * 0.98;
        shapes[i].position = shapes[i].position + shapes[i].velocity;
        
        if (dist.length() < limit) {
            shapes[i].position = shapes[i].pin;
        }
        
        // Update shape with new values
        shapes[i].update();
        
        // Add shape to vboMesh
        for (int j = 0; j < shapes[i].getVertices().size(); j++) {
            vboMesh.addVertex(shapes[i].getVertex(j) + shapes[i].position);
            vboMesh.addColor(shapes[i].getColor(j));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    vboMesh.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i].inArea(x, y)) {
            shapes[i].position.set(x, y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}
