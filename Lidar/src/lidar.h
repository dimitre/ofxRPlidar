ofxMicroUI * uiLidar = &u.uis["lidar"];
ofxMicroUI * uiRects = &u.uis["rects"];

ofRectangle stage;
ofRectangle alvo;

float offAngle = -90;

//bool has = false;
//bool oldHas = false;

//ofRectangle

struct detection {
public:
	
	ofRectangle stage;
	ofRectangle alvo;
	float scale = 1.0;
	
	bool has = false;
	bool oldHas = false;
	glm::vec2 det { 0.0, 0.0 };
	glm::vec2 pos { 0.0, 0.0 };
	glm::vec2 posStage { 0.0, 0.0 };
	glm::vec2 posAlvo { 0.0, 0.0 };
	bool inside = false;
	bool limpa = false;

	ofxOscSender sender;

	void setupOsc() {
		ofxOscSenderSettings set;
		set.host = "127.0.0.1";
		set.port = 8000;
		set.broadcast = true;
		sender.setup(set);

	}
	
	void setPos(glm::vec2 v) {
		det = v;
		cout << "detection setPos " << v << endl;
//		cout << det << endl;

		inside = alvo.inside(pos);
		
		pos = glm::vec2 {
			det.x * scale,
			det.y * scale
		};
		
		posStage = glm::vec2 {
			ofMap(pos.x, stage.x, stage.x + stage.width, 0.0, 1.0),
			ofMap(pos.y, stage.y, stage.y + stage.height, 0.0, 1.0),
		};
		posAlvo = glm::vec2 {
			ofMap(pos.x, alvo.x, alvo.x + alvo.width, 0.0, 1.0),
			ofMap(pos.y, alvo.y, alvo.y + alvo.height, 0.0, 1.0),
		};

		sendOsc();

		// FIXME: sendOsc pode ser aqui dentro.
	}
	
	void sendOsc() {
		cout << "sendOsc" << endl;
		{
			ofxOscMessage m;
			string status { "limpa" };
			if (has && inside) {
				status = "dentro";
			}
			if (has && !inside) {
				status = "fora";
			}
			m.setAddress("/status");
			m.addStringArg(status);
			sender.sendMessage(m, false);
			cout << "	/status/" << status << endl;
		}
		
		if (has) {
			{
				ofxOscMessage m;
				m.setAddress("/pos");
				m.addFloatArg(det.x);
				m.addFloatArg(det.y);
				sender.sendMessage(m, false);
			}
			{
				ofxOscMessage m;
				m.setAddress("/posStage");

				m.addFloatArg(posStage.x);
				m.addFloatArg(posStage.y);
				sender.sendMessage(m, false);

			}
			{
				ofxOscMessage m;
				m.setAddress("/posAlvo");
				m.addFloatArg(posAlvo.x);
				m.addFloatArg(posAlvo.y);
				sender.sendMessage(m, false);
			}
			
			cout << "	/pos/" << det << endl;
			cout << "	/posStage/" << posStage << endl;
			cout << "	/posAlvo/" << posAlvo << endl;
		}
	}
	

	
	void draw() {
		ofPushStyle();

		ofNoFill();
		ofSetColor(0, 0, 255);
		ofDrawRectangle(stage);
	   ofSetColor(0, 255, 0);
	   ofDrawRectangle(alvo);
		
		if (has) {
			
			if (inside) {
				ofSetColor(0, 255, 0);
			} else {
				ofSetColor(0, 0, 255);
			}

			//			cout << det.x << endl;
			//			cout << det.x * uiLidar->pFloat["scale"] << endl;
			//			ofDrawCircle(det.x * uiLidar->pFloat["scale"], det.y * uiLidar->pFloat["scale"], 8.0);
			ofDrawCircle(pos.x, pos.y, 8.0);
		}
		ofPopStyle();

	}
} machado;

glm::vec2 polarToCartesian(float angle, float m) {
	float a { glm::radians(angle) };
	return { m * std::cos(a), m * std::sin(a) };
}


void lidarDraw() {
	ofPushMatrix();
	ofTranslate(glm::vec2(ofGetWindowWidth(), ofGetWindowHeight())*.5f);

	float scale = uiLidar->pFloat["scale"];
	machado.scale = scale;
	machado.stage = ofRectangle(
						uiRects->pFloat["sx"] * scale,
						uiRects->pFloat["sy"] * scale,
						uiRects->pFloat["swidth"] * scale,
						uiRects->pFloat["sheight"] * scale
					);
	
	machado.alvo = ofRectangle(
						uiRects->pFloat["ax"] * scale,
						uiRects->pFloat["ay"] * scale,
						uiRects->pFloat["awidth"] * scale,
						uiRects->pFloat["aheight"] * scale
					   );

//	stage.draw();

	ofSetColor(255);
	for(auto &s : sensors_) {
		s->update();
		auto data = s->getResult();
		ofSetColor(255, 0, 80);
		ofDrawRectangle(-5, -5, 10, 10);


		machado.has = false;
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
							machado.has = true;
						}
					}
				}

			}
		}

		if (machado.oldHas != machado.has) {
			machado.oldHas = machado.has;
			if (!uiLidar->pBool["continuous"]) {
				if (machado.has) {
					soma /= positions.size();
					machado.setPos(soma);
				}
			}
//			cout << "CHANGE " << has << endl;
		}

		if (uiLidar->pBool["continuous"]) {
			if (machado.has) {
				soma /= positions.size();
				machado.setPos(soma);
//				sendOsc();
			}
		}

		//		cout << det << endl;

		machado.draw();
//		if (machado.has) {
//
//		}

		ofPath path;
		path.setCircleResolution(120);
		float r = uiLidar->pFloat["minDistance"] * uiLidar->pFloat["scale"];
		path.arc(0, 0, r, r, uiLidar->pFloat["minAngle"] + offAngle, uiLidar->pFloat["maxAngle"] + offAngle);
		path.setFilled(false);
		path.setStrokeWidth(1);
		path.draw();

	}
	ofPopMatrix();

}


void lidarExit() {
	for(auto &s : sensors_) {
		cout << s->stop() << endl;
	}
}

void lidarSetup() {
	machado.setupOsc();

	auto sensor_list = ofxRPlidar::getDeviceList();
	for(auto &sensor_info : sensor_list) {
		auto sensor = make_shared<ofxRPlidar>();
		if(sensor->connect(sensor_info.getDevicePath())) {
			sensor->start();
			sensors_.push_back(sensor);
		}
	}
}
