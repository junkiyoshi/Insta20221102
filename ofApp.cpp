#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(5);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int span = 30;
	int size = span * 0.75;

	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 0, 255) };

	for (int i = 0; i < color_list.size(); i++) {

		auto color = color_list[i];
		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

		for (int x = span * -12; x <= span * 12; x += span) {

			auto noise_y = ofMap(ofNoise(noise_seed.x, x * 0.003 + ofGetFrameNum() * 0.005), 0, 1, span * -12, span * 12);

			for (int y = span * -12; y <= span * 12; y += span) {

				auto gap_y = abs(noise_y - y);
				auto alpha = 0;
				if (gap_y <= span * 3) {

					alpha = ofMap(gap_y, 0, span * 3, 255, 0);
				}
				auto height = ofMap(alpha, 0, 255, 0, span * 6);

				if (alpha > 0) {

					ofFill();
					ofSetColor(ofColor(0));
					ofDrawBox(glm::vec3(x, y, height * 0.5), size, size, height);

					ofNoFill();
					ofSetColor(color);
					ofDrawBox(glm::vec3(x, y, height * 0.5), size, size, height);
				}

				ofSetColor(128);
				ofDrawRectangle(x, y, size, size);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}