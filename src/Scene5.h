//
//  Scene5.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.

#ifndef __leapTest__Scene5__
#define __leapTest__Scene5__

#include <iostream>
#include "ofxState.h"
#include "SharedData.h"
//#include "ofxFluid.h"
#include "ofxOsc.h"
#include "ofxTrueTypeFontUC.h"

#include "Bacteria.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

#define SENDIP "localhost"
//#define SENDIP "157.82.5.78"
#define SENDPORT 12346

#endif /* defined(__leapTest__Scene5__) */

//ゲームクリア
class Scene5 : public itg::ofxState<SharedData>{
    void setup();
    void update();
    void draw();
    
    void stateEnter();
    void stateExit();
    
    void keyPressed  (int key) ;
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    /*
    //指先のディスプレイ座標
    float fingerPosX[15];
    float fingerPosY[15];
    
    //流体のパラメータ
    ofxFluid fluid;
    float fogDensity;
    ofVec2f oldM;
    int blueColor;//青に近づいていく
    float rand;//流体の大きさ
    
    //流体のテスト用
    int     mouseX, mouseY;
    */
    //ウェブカム映像のハンドリング
    //ofVideoGrabber vidGrabber;
    //int camWidth;
    //int camHeight;
    
    float i1X, i1Y, i2X, i2Y, i3X, i3Y, i4X, i4Y;
    
    ofxTrueTypeFontUC  clearWord;
    Boolean nextView;
    
    ofxOscSender sender;
    
    string getName();
    
    //バクテリア
    Bacteria bacteria[2];
    
    //水
    ofImage water;
};