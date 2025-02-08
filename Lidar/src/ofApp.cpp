#include "ofApp.h"

//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/polar_coordinates.hpp>
#include <glm/vec3.hpp>


glm::vec2 polarToCartesian(float angle, float m) {
	float a { glm::radians(angle) };
	return { m * std::cos(a), m * std::sin(a) };
}

bool has = false;
bool oldHas = false;
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
	ofSetColor(255);

	for(auto &s : sensors_) {
		s->update();
		auto data = s->getResult();
		ofPushMatrix();
		ofTranslate(glm::vec2(ofGetWidth(), ofGetHeight())/2.f);
		ofSetColor(255, 0, 80);
		ofDrawRectangle(-5, -5, 10, 10);

		
		has = false;
		vector <glm::vec2> positions;
		glm::vec2 soma { 0.0, 0.0 };
		glm::vec2 det { 0.0, 0.0 };
		
		for(auto &d : data) {
			if(d.quality > 0) {
				
				if (d.distance < u.pFloat["minDistance"]) {
					if (d.angle < u.pFloat["maxAngle"] && d.angle > u.pFloat["minAngle"])
					{
//						cout << d.angle << endl;
						glm::vec2 pos = polarToCartesian(d.angle + 90, d.distance * u.pFloat["scale"]);
						positions.emplace_back(pos);
						soma += pos;
						ofDrawCircle(pos, 3);
						
						if (positions.size() > 2) {
							has = true;
						}
					}
				}
				
			}
		}
		
		if (oldHas != has) {
			oldHas = has;
			cout << "CHANGE " << has << endl;
			
			if (has) {
				soma /= positions.size();
				det = soma;
				cout << det << endl;
				
			}
		}
		
		if (has) {
			ofNoFill();
			ofSetColor(0, 255, 0);
			ofDrawCircle(det.x * u.pFloat["scale"], det.y * u.pFloat["scale"], 16, 16);

		}
		
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
