#include "ofApp.h"

void ofApp::setup() {
    
    ofAddListener(camera.CAMERA_ADDED, this, &ofApp::onCameraAdded);
    ofAddListener(camera.CAMERA_REMOVED, this, &ofApp::onCameraRemoved);
    ofAddListener(camera.LIVE_VIEW_STARTED, this, &ofApp::onLiveViewStarted);
    ofAddListener(camera.LIVE_VIEW_STOPPED, this, &ofApp::onLiveViewStopped);
    
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    bIsRecordingMovie = false;
	camera.setup();
}

void ofApp::exit() {
    camera.close();
}

void ofApp::update() {
    camera.update();
	if(camera.isFrameNew()) {
		// process the live view with camera.getLivePixels()
	}
    
	if(camera.isPhotoNew()) {
		// process the photo with camera.getPhotoPixels()
		// or just save the photo to disk (jpg only):
		camera.savePhoto(ofToString(ofGetFrameNum()) + ".jpg");
	}
    
    if(camera.isMovieNew()) {
		camera.savePhoto(ofToString(ofGetFrameNum()) + ".mov");
	}
}

void ofApp::draw() {
	camera.draw(0, 0);
	// camera.drawPhoto(0, 0, 432, 288);

	if(camera.isLiveDataReady()) {
		stringstream status;
        status << camera.getWidth() << "x" << camera.getHeight() << " @ " <<
			(int) ofGetFrameRate() << " app-fps / " <<
			(int) camera.getFrameRate() << " cam-fps / " <<
            (camera.getBandwidth() / (1<<20)) << " MiB/s";
		ofDrawBitmapString(status.str(), 10, 20);
	}
}

void ofApp::keyPressed(int key) {
	if(key == ' ') {
		camera.takePhoto();
    }
    if(key == 's') {
        camera.setup();
    }
    if(key == 'c') {
        camera.close();
    }
    else if(key == 'v') {
        bIsRecordingMovie ^= true;
        if (bIsRecordingMovie) {
            camera.beginMovieRecording();
        } else {
            camera.endMovieRecording();
        }
	}

}

void ofApp::onCameraAdded(ofEventArgs &)
{
    ofLogNotice(__PRETTY_FUNCTION__) << "camera added";
}

void ofApp::onCameraRemoved(ofEventArgs &)
{
    ofLogNotice(__PRETTY_FUNCTION__) << "camera removed";
}

void ofApp::onLiveViewStarted(ofEventArgs &)
{
    ofLogNotice(__PRETTY_FUNCTION__) << "live view started";
}

void ofApp::onLiveViewStopped(ofEventArgs &)
{
    ofLogNotice(__PRETTY_FUNCTION__) << "live view stopped";
}
