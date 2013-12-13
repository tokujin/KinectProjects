#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxOsc.h"


class testApp : public ofBaseApp{
    
public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    void joints_numbering();
    
    //OpenNI related
    void userEvent(ofxOpenNIUserEvent & event);
	ofxOpenNI openNIDevice;
    
    ofVec3f torso;
    ofVec3f neck;
    ofVec3f head;
    
    ofVec3f leftShoulder;
    ofVec3f leftElbow;
    ofVec3f leftHand;
    ofVec3f rightShoulder;
    ofVec3f rightElbow;
    ofVec3f rightHand;
    
    ofVec3f leftHip;
    ofVec3f leftKnee;
    ofVec3f leftFoot;

    ofVec3f rightHip;
    ofVec3f rightKnee;
    ofVec3f rightFoot;
    
    ofVec3f joints[15];
    
    ofVec3f centerHand;
    
    //Osc related
    ofxOscSender mSender;
    ofVec3f pos,vel;

    //others
    ofTrueTypeFont verdana;
        
};

#endif