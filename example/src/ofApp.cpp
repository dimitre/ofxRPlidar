#include "ofApp.h"

//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/polar_coordinates.hpp>

glm::vec2 polarToCartesian(float angle, float m) {
	float a { glm::radians(angle) };
	return { m * std::cos(a), m * std::sin(a) };
}

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
		ofSetColor(255);
		s->update();
		auto data = s->getResult();
		ofPushMatrix();
		ofTranslate(glm::vec2(ofGetWidth(), ofGetHeight())/2.f);
		for(auto &d : data) {
			if(d.quality > 0)
			{
				glm::vec2 pos = polarToCartesian(d.angle + 90, d.distance * 0.5);
				ofDrawCircle(pos, 3);
				
//				ofSetColor(0, 255, 0);
//				ofVec2f pos = ofVec2f(d.distance * 0.5 , 0).getRotated(d.angle + 90);
//				ofDrawCircle(pos, 3);
			}
		}
		
		ofSetColor(255, 0, 80);
		ofDrawRectangle(-5, -5, 10, 10);
		ofPopMatrix();
	}
}

void ofApp::exit(){
	for(auto &s : sensors_) {
		cout << s->stop() << endl; 
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
