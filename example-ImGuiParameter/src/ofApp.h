#pragma once

#include "ofMain.h"
#include "SharedSettings.h"
#include "Camera.h"
#include "ofxImGuiParameter.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
	void addListeners();
	void removeListeners();

	// special callbacks
	void addFiveAndResend(int & value);
	void updateCameraInfo_str(bool & value);
	void disableThird(int & value);
	void checkMaxTwo(ofVec4f & value);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(float x, float y);

	SharedSettings sharedSettings;
	Camera camera;



//	bool needsUpdate;
};