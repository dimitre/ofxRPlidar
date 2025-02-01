#pragma once

#include "ofMain.h"
#include "ofxRPlidar.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
private:
	std::vector<std::shared_ptr<ofxRPlidar>> sensors_;
};
