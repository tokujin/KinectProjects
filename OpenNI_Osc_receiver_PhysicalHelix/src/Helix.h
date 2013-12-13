//
//  Helix.h
//  helix03
//
//  Created by Norihito Yuki on 12/13/13.
//
//

#pragma once
#include "ofMain.h"
#ifndef __helix03__Helix__
#define __helix03__Helix__


class Helix : public ofBaseApp{
    
public:
    
    void setup(ofVec3f _p, ofVec3f _q);
    void update();
    void draw();
    void transfer();
  
    //helix related
    ofVec3f p, q;  // these points will be substituted by joints data
    ofVec3f a[300], b[300], c[300];
    float angle1, angle2;
    ofVec3f nx, ny, nz;
    float L;
    float magnitude;
    ofVec3f pos;
    ofVec3f test_point;


};



#endif /* defined(__helix03__Helix__) */
