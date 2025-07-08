#include "ofApp.h"

//#include <glm/vec3.hpp>

void ofApp::setup() {
	ofSetFrameRate(24);
//	ofSetFrameRate(0);
//	ofSetVerticalSync(false);
	lidarSetup();
}

void ofApp::update() {
	lidarUpdateBlobs();
//	lidarUpdate();
}

void ofApp::draw() {
    ofBackground(30);
	if (!sensors_.size()) {
		ofDrawBitmapString("Lidar n. encontrado, Simulador de machado no mouse", 400, 20);
	}
	// if (sensors_.size()) {
	lidarDraw();
	// } else {
	// testDraw();
	// }
}

void ofApp::exit() {
//	lidarExit();
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mousePressed(int x, int y, int button) {

	if (uiLidar->pBool["mouse"]) {
		// cout << "mousePressed button " << button << endl;
		if (button == 2) {
			// teste.clear();
			machado.clear();
		} else {
			machado.has = true;
			glm::vec2 pos { x - ofGetWindowWidth() * .5f - machado.offset.x,
				y - ofGetWindowHeight() * .5f - machado.offset.y }
			;
			machado.setPos(pos);
			// teste.mouse({x, y});
		}
	}
}
