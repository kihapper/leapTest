//
//  Scene1.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.

#ifndef __leapTest__Scene1__
#define __leapTest__Scene1__

#include <iostream>
#include "ofxState.h"
#include "SharedData.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxOsc.h"

#endif /* defined(__leapTest__Scene1__) */

#define SENDIP "localhost"
#define SENDPORT 12346

//手元のカメラ
class Scene1 : public itg::ofxState<SharedData>{
    void setup();
    void update();
    void draw();
    
    void stateEnter();
    void stateExit();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

    
    ofVideoGrabber vidGrabber;
    ofQTKitGrabber QTTest;
    
    int camWidth;
    int camHeight;
    
    string getName();
    
    Boolean onHuman;
    
    //フォント
    ofxTrueTypeFontUC  iFont;
    float i1X, i1Y, i2X, i2Y, i3X, i3Y;
    
    Boolean setHand;
    Boolean pushed;
    
    int checkCounter;
    
    ofxOscSender sender;

};