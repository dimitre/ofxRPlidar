#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofWindowSettings settings;
//	settings.setGLVersion(3, 2);
	settings.setSize(1000, 1000);
	settings.highResolutionCapable = false;

	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
