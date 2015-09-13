#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	circleTex.load("circle.png");
    
    float radius = 4;
    float nbX = ofGetWidth() / (radius * 2) + 1;
    float nbY = ofGetHeight() / (radius * 2) + 1;

    vboMesh.setUsage(GL_DYNAMIC_DRAW);
    vboMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int y = 0; y < nbY; y++) {
        for (int x = 0; x < nbX; x++) {
            shapes.emplace_back();
            float posx = x * radius * 2;
            float posy = y * radius * 2;
            //ofColor c = image.getColor(x, y);
            ofColor c = ofColor(ofRandom(130, 180));
            shapes.back().setup(posx , posy, radius, c);
			vboMesh.addVertex(shapes.back().pin);
			vboMesh.addColor(c);
        }
    }

    ofSetBackgroundColor(0);
    glPointSize(radius*2);

    shader.load("vert.glsl","frag.glsl");
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0;i<shapes.size();i++) {
        shapes[i].update();
        vboMesh.getVertices()[i] = shapes[i].position;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();
	circleTex.bind();
    vboMesh.draw();
    circleTex.unbind();
    shader.end();
    
    ofDrawBitmapString(ofGetFrameRate(),20,20);
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
    for (int i=0;i<shapes.size();i++) {
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
