#pragma once

#include "ofMain.h"
#include "ofxRPlidar.h"
#include "ofxMicroUI.h"
//#include "ofxMicroUISoftware.h"


class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	ofxMicroUI u { "u.txt" };
	
private:
	std::vector<std::shared_ptr<ofxRPlidar>> sensors_;
	
};
