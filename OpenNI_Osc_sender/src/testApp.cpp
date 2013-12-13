#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    //general settings
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    //OpenNI related settings
    ofSetLogLevel(OF_LOG_VERBOSE);
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // you can alternatively create a 'base' user class
    //    ofxOpenNIUser user;
    //    user.setUseMaskTexture(true);
    //    user.setUsePointCloud(true);
    //    user.setPointCloudDrawSize(2);
    //    user.setPointCloudResolution(2);
    //    openNIDevice.setBaseUserClass(user);
    
    //Osc related
    mSender.setup("localhost", 12345);
    pos = ofGetWindowSize()/2;

    //display related
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);

    
}

//--------------------------------------------------------------
void testApp::update(){

    //Osc related
    ofxOscMessage m2;
    m2.setAddress("/ball/pos");
    for (int i=0; i<15; i++) {
        m2.addIntArg(joints[i].x);
        m2.addIntArg(joints[i].y);
        m2.addIntArg(joints[i].z);

    }
    mSender.sendMessage(m2);
    //OpenNI related
    openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
	ofSetColor(255, 255, 255);
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        //        user.drawMask();
        ofSetColor(0,0,0,20);
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(255,255,255,100);
        
        //nori edit
        // if you want x-coordinate leftHand.x
        ofPushMatrix();
        ofScale(1.6,1.6,1); //super hacky by michael.

        torso = user.getJoint(JOINT_TORSO).getProjectivePosition();
        neck = user.getJoint(JOINT_NECK).getProjectivePosition();
        head = user.getJoint(JOINT_HEAD).getProjectivePosition();
        
        leftShoulder = user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
        leftElbow = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition();
        leftHand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        rightShoulder = user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
        rightElbow = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition();
        rightHand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        
        leftHip = user.getJoint(JOINT_LEFT_HIP).getProjectivePosition();
        leftKnee = user.getJoint(JOINT_LEFT_KNEE).getProjectivePosition();
        leftFoot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        
        rightHip = user.getJoint(JOINT_RIGHT_HIP).getProjectivePosition();
        rightKnee = user.getJoint(JOINT_RIGHT_KNEE).getProjectivePosition();
        rightFoot = user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        joints_numbering();

        ofSetColor(0,150,255);
        ofCircle(leftHand, 10);
        
        ofSetColor(255,0,150);
        ofCircle(rightHand, 10);
        //        openNIDevice.drawSkeletons(0, 0, ofGetWidth(), ofGetHeight());
        openNIDevice.drawSkeletons();
        
        ofPopMatrix();
        
        // you can also access the pixel and texture references individually:
        
        // TEXTURE REFERENCE
        //ofTexture & tex = user.getMaskTextureReference();
        // do something with texture...
        
        // PIXEL REFERENCE
        //ofPixels & pix = user.getMaskPixels();
        // do something with the pixels...
        
        // and point clouds:
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        
    }
    
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    cout << "torso x; " << torso.x << " y; " << torso.y << " z; " <<torso.z <<endl;
    // draw some info regarding frame counts etc
    //	ofSetColor(0, 255, 0);
    //	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
    //	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    //  ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::joints_numbering(){
    joints[0] = torso;
    joints[1] = neck;
    joints[2] = head;
    joints[3] = leftShoulder;
    joints[4] = leftElbow;
    joints[5] = leftHand;
    joints[6] = rightShoulder;
    joints[7] = rightElbow;
    joints[8] = rightHand;
    joints[9] = leftHip;
    joints[10] = leftKnee;
    joints[11] = leftFoot;
    joints[12] = rightHip;
    joints[13] = rightKnee;
    joints[14] = rightFoot;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
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