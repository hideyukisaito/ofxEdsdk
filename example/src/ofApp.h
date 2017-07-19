#pragma once

#include "ofMain.h"

#include "ofxEdsdk.h"

class ofApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofxEdsdk::Camera camera;
    
    bool bIsRecordingMovie;
    
    void onCameraAdded(ofEventArgs &);
    void onCameraRemoved(ofEventArgs &);
    void onLiveViewStarted(ofEventArgs &);
    void onLiveViewStopped(ofEventArgs &);
};
