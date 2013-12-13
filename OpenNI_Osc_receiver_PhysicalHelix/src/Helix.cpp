//
//  Helix.cpp
//  helix03
//
//  Created by Norihito Yuki on 12/13/13.
//
//

#include "Helix.h"
//--------------------------------------------------------------
void Helix::setup(ofVec3f _p, ofVec3f _q){
    nx=ofVec3f(1,0,0), ny=ofVec3f(0,1,0), nz=ofVec3f(0,0,1);
    p = _p;
    q = _q;
    L = (q-p).length();
}

//--------------------------------------------------------------
void Helix::update(){
    
    //between push and pop, conduct coordinate transformation
    ofPushMatrix();
        ofTranslate(p);  //first translate the origin to point p
        ofVec3f projected_vector = ofVec3f((q-p).x, (q-p).y, 0);  //project vecotor (q-p) to x,y plain
        //note that both cases (q-p).z>0 and (q-p).z<0 are projected to xy plain, so it is necessary to make case statements later before rotate angle2
        //angle method returns float from 0 to 180!!, so making case statements is necesarry
        if ((q-p).y>0) {
            angle1 = nx.angle(projected_vector);
        }
        if ((q-p).y<0) {
            angle1 = 360 - nx.angle(projected_vector);
        }
        ofRotate(angle1, 0, 0, 1);
        if((q-p).z>0 || (q-p).z==0){
            angle2 = -projected_vector.angle(q-p);
        }
        if((q-p).z<0){
            angle2 = projected_vector.angle(q-p);
        }
        ofRotate(angle2, 0, 1, 0);  //rotation around y

        //parameter settings
        float temp = ofGetElapsedTimef()*10;
        magnitude = ofMap(sin(temp*0.5), -1, 1, 38, 40);
    
        test_point = ofVec3f(L, 0, 0);
        //make 3 strings
        for (int theta=0; theta<300; theta++) {
            a[theta] = ofVec3f(L/300 * theta, magnitude * cos(theta*0.1 + temp), magnitude * sin(theta*0.1 +temp));
            b[theta] = ofVec3f(L/300 * theta, magnitude * cos(theta*0.1 + temp + PI/5), magnitude * sin(theta*0.1 +temp + PI/5));
            c[theta] = ofVec3f(L/300 * theta, magnitude * cos(theta*0.1 + temp + PI/3), magnitude * sin(theta*0.1 +temp + PI/3));
        }
    ofPopMatrix();

}

//--------------------------------------------------------------
void Helix::draw(){
    ofSetColor(255);
    ofCircle(p, 20);
    ofCircle(q, 20);
    ofPushMatrix();
    ofTranslate(p);
    ofRotate(angle1, 0, 0, 1);
    ofRotate(angle2, 0, 1, 0);
    for (int i=0; i<300; i++) {
        ofSetColor(200, 30, 45);
        ofCircle(a[i], 1);
        ofSetColor(45, 200, 30);
        ofCircle(b[i], 1);
        ofSetColor(30, 45, 200);
        ofCircle(c[i], 1);
    }
    ofPopMatrix();
}