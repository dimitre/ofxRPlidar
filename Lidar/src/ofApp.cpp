#include "ofApp.h"

//#include <glm/vec3.hpp>

void ofApp::setup(){
	lidarSetup();
}

void ofApp::update(){
}

void ofApp::draw(){
	lidarDraw();
}

void ofApp::exit(){
	lidarExit();
}

void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}
