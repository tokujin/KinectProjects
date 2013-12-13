#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //general settings
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    //Osc related
    mReceiver.setup(12345);
    //camera related
    ofEnableDepthTest();
    myCam.setDistance(500);
    //Helixrelated
    
    //OpenNI related
    for (int i=0; i<15; i++) {
        joints[i].x = -ofGetWidth()/2;
        joints[i].y = -ofGetWidth()/2;
        joints[i].z = -ofGetWidth()/2;
    }
}

//--------------------------------------------------------------
void testApp::update(){
    ofPushMatrix();
    myHelix.setup(joints[4], joints[5]);
    myHelix.update();
    ofPopMatrix();
    checkOsc();
    
    cout << "x: "<<joints[5].x << " y: "<< joints[5].y << " z: "<< joints[5].z <<endl;
}

//--------------------------------------------------------------
void testApp::draw(){

//    myCam.begin();
    ofPushMatrix();
  ofScale(1.6,1.6, 1);
    //joints
    joints_draw();
    myHelix.draw();
    
    ofPopMatrix();
//    myCam.end();

}

//--------------------------------------------------------------
void testApp::checkOsc(){
    while (mReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        mReceiver.getNextMessage(&m);
        string addr=m.getAddress();
        
        for (int i=0; i<15; i++) {
            joints[i].x = m.getArgAsInt32(i*3);
            joints[i].y = m.getArgAsInt32(i*3+1);
            joints[i].z = ofMap(m.getArgAsInt32(i*3+2), 1000, 2100, 200, 400);
            ;
        }
        
        joints_naming();
    }
}

//--------------------------------------------------------------
void testApp::joints_draw(){
    
    ofSetColor(200);
    for (int i=0; i<15; i++) {
        if((i==5) || (i==6)){
            ofSetColor(255, 0, 0);
            ofDrawSphere(joints[i], 20);
//            ofCircle(joints[i].x, joints[i].y, 10);
        }
        else{
            ofSetColor(200);
            ofDrawSphere(joints[i], 20);
//            ofCircle(joints[i].x, joints[i].y, 10);
        }
    }
};

void testApp::joints_naming(){
    torso.set(joints[0].x,joints[0].y, joints[0].z);
    neck.set(joints[1].x,joints[1].y, joints[1].z);
    head.set(joints[2].x,joints[2].y, joints[2].z);
    leftShoulder.set(joints[3].x,joints[3].y, joints[3].z);
    leftElbow.set(joints[4].x,joints[4].y, joints[4].z);
    leftHand.set(joints[5].x,joints[5].y, joints[5].z);
    rightShoulder.set(joints[6].x,joints[6].y, joints[6].z);
    rightElbow.set(joints[7].x,joints[7].y, joints[7].z);
    rightHand.set(joints[8].x,joints[8].y, joints[8].z);
    leftHip.set(joints[9].x,joints[9].y, joints[9].z);
    leftKnee.set(joints[10].x,joints[10].y, joints[10].z);
    leftFoot.set(joints[11].x,joints[11].y, joints[11].z);
    rightHip.set(joints[12].x,joints[12].y, joints[12].z);
    rightKnee.set(joints[13].x,joints[13].y, joints[13].z);
    rightFoot.set(joints[14].x,joints[14].y, joints[14].z);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
