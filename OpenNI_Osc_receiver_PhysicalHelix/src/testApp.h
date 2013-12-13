#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Helix.h"
#include "ofxUI.h"


class testApp : public ofBaseApp{
    
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void joints_draw();
    void joints_naming();

    //helix related
    ofVec3f p, q;  // these points will be substituted by joints data
    
    //eaty cam
    ofEasyCam   myCam;
    
    Helix myHelix;
    
    //test
    ofVec2f pos, vel;
    
    //gui related
    ofxUICanvas *gui;
    void setupGUI();
    void guiEvent(ofxUIEventArgs $e);

    //Osc and OpenNI related
    void checkOsc();
    ofxOscReceiver mReceiver;
    ofVec3f mousePos;
    ofVec3f ballPosL;
    ofVec3f ballPosR;
    
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

};
