#include "ofApp.h"

//#include <glm/vec3.hpp>

void ofApp::setup(){
	lidarSetup();
}

void ofApp::update(){
}

void ofApp::draw(){

    // if (sensors_.size()) {
	lidarDraw();
    // } else {
        // testDraw();
    // }
}

void ofApp::exit(){
	lidarExit();
}

void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}

void ofApp::mousePressed(int x, int y, int button) {

    // cout << "mousePressed button " << button << endl;
    if (button == 2) {
        // teste.clear();
        machado.clear();
    } else {
        machado.has = true;
        float r = machado.scale;
        glm::vec2 pos =  glm::vec2{ x - ofGetWindowWidth() * .5f, y - ofGetWindowHeight() * .5f } / r;
        machado.setPos(pos);
    // teste.mouse({x, y});
    }
}
