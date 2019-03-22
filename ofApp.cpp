#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofColor color;
	for (int v = 0; v < 360; v += 10) {

		for (int u = 0; u < 360; u += 20) {

			color.setHsb(ofMap(v, 0, 360, 0, 255), 255, 230);
			ofSetColor(color);

			ofBeginShape();

			ofVertex(this->make_point(300, 70, u, v));
			ofVertex(this->make_point(300, 70, u + 20, v));
			ofVertex(this->make_point(300, 70, u + 20, v + 10));
			ofVertex(this->make_point(300, 70, u, v + 10));

			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	float x = (R + r * cos(u)) * cos(v);
	float y = (R + r * cos(u)) * sin(v);
	float z = r * sin(u);

	auto location = glm::vec3(x, y, z);
	auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(location.y * 0.001 + ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
	location = glm::vec4(location, 0) * rotation_y;

	return location;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}