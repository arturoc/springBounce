#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#if OF_VERSION_MINOR==9
	ofGLWindowSettings settings;
	settings.setGLVersion(3,2);
	settings.width = 1280;
	settings.height = 720;
	ofCreateWindow(settings);
#else
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1280,720,OF_WINDOW);
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
