#pragma once

#include "ofMain.h"
#include "ofxMicroUI.h"
#include "ofxMicroUISoftware.h"
#include "ofxRPlidar.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);

	void mousePressed(int x, int y, int button);


	ofxMicroUI u { "u.txt" };
	ofxMicroUISoftware soft { &u, "EmptyUIScenes", 1 };

#include "lidar.h"

private:
	std::vector<std::shared_ptr<ofxRPlidar>> sensors_;

};
