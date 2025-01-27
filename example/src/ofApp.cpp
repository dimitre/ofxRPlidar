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
				
				ofVec2f pos = ofVec2f(d.distance, 0).getRotated(d.angle);
				ofDrawCircle(pos, 5);
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

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
