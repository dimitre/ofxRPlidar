ofxMicroUI * uiLidar = &u.uis["lidar"];
ofxMicroUI * uiRects = &u.uis["rects"];

ofxOscSender sender;
float offAngle = -90;
glm::vec2 det { 0.0, 0.0 };

bool has = false;
bool oldHas = false;

ofRectangle stage;
//ofRectangle


glm::vec2 polarToCartesian(float angle, float m) {
	float a { glm::radians(angle) };
	return { m * std::cos(a), m * std::sin(a) };
}


void sendOsc() {
	ofxOscMessage m;

	if (has) {
		m.setAddress("/machado");
		m.addFloatArg(det.x);
		m.addFloatArg(det.y);
		sender.sendMessage(m, false);
	} else {
		m.setAddress("/limpa");
		m.addFloatArg(0.0);
		sender.sendMessage(m, false);
	}
}

void lidarDraw() {
	stage = ofRectangle(uiRects->pFloat["sx"], uiRects->pFloat["sy"], uiRects->pFloat["swidth"], uiRects->pFloat["sheight"]);
	ofNoFill();
	ofSetColor(0, 0, 255);
	ofDrawRectangle(stage);
	ofFill();
//	stage.draw();

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

		for(auto &d : data) {
			if(d.quality > 0) {

				if (d.distance < uiLidar->pFloat["minDistance"]) {
				if (d.angle < uiLidar->pFloat["maxAngle"] && d.angle > uiLidar->pFloat["minAngle"])
					{
						//						cout << d.angle << endl;
						glm::vec2 pos = polarToCartesian(d.angle + offAngle, d.distance);
						positions.emplace_back(pos);
						soma += pos;
						ofDrawCircle(pos * uiLidar->pFloat["scale"], 3);

						if (positions.size() > 2) {
							has = true;
						}
					}
				}

			}
		}

		if (oldHas != has) {
			oldHas = has;
			if (!uiLidar->pBool["continuous"]) {
				if (has) {
					soma /= positions.size();
					det = soma;
					cout << det << endl;
				}
			}
			cout << "CHANGE " << has << endl;
			sendOsc();
		}

		if (uiLidar->pBool["continuous"]) {
			if (has) {
				soma /= positions.size();
				det = soma;
				sendOsc();
				//			cout << det << endl;
			}
		}

		//		cout << det << endl;

		if (has) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(0, 255, 0);
			//			cout << det.x << endl;
			//			cout << det.x * uiLidar->pFloat["scale"] << endl;
			//			ofDrawCircle(det.x * uiLidar->pFloat["scale"], det.y * uiLidar->pFloat["scale"], 8.0);
			ofDrawCircle(det.x * uiLidar->pFloat["scale"], det.y * uiLidar->pFloat["scale"], 8.0);
			ofPopStyle();
		}

		ofPath path;
		path.setCircleResolution(120);
		float r = uiLidar->pFloat["minDistance"] * uiLidar->pFloat["scale"];
		path.arc(0, 0, r, r, uiLidar->pFloat["minAngle"] + offAngle, uiLidar->pFloat["maxAngle"] + offAngle);
		path.setFilled(false);
		path.setStrokeWidth(1);
		path.draw();

		ofPopMatrix();
	}
}


void lidarExit() {
	for(auto &s : sensors_) {
		cout << s->stop() << endl;
	}
}

void lidarSetup() {
	ofxOscSenderSettings set;
	set.host = "127.0.0.1";
	set.port = 8000;
	set.broadcast = true;
	sender.setup(set);

	auto sensor_list = ofxRPlidar::getDeviceList();
	for(auto &sensor_info : sensor_list) {
		auto sensor = make_shared<ofxRPlidar>();
		if(sensor->connect(sensor_info.getDevicePath())) {
			sensor->start();
			sensors_.push_back(sensor);
		}
	}
}
