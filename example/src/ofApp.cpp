#include "ofApp.h"
#include "ofVec2f.h"

//--------------------------------------------------------------
void ofApp::setup(){
	auto sensor_list = ofxRPlidar::getDeviceList();
	for(auto &sensor_info : sensor_list) {
		auto sensor = make_shared<ofxRPlidar>();
		if(sensor->connect(sensor_info.getDevicePath())) {
			sensor->start();
			sensors_.push_back(sensor);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	for(auto &s : sensors_) {
		s->update();
		auto data = s->getResult();
		ofPushMatrix();
		ofTranslate(glm::vec2(ofGetWidth(), ofGetHeight())/2.f);
		for(auto &d : data) {
			if(d.quality > 0) {
				ofVec2f pos = ofVec2f(d.distance*.2, 0).getRotated(d.angle);
				ofDrawCircle(pos, 3);
			}
		}
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
