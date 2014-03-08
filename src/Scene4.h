//
//  Scene4.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.

#ifndef __leapTest__Scene4__
#define __leapTest__Scene4__

#include <iostream>
#include "ofxState.h"
#include "SharedData.h"
//#include "ofxFluid.h"
#include "ofxOsc.h"
#include "ofxTrueTypeFontUC.h"

#include "Bacteria.h"

#endif /* defined(__leapTest__Scene4__) */

#define SENDIP "localhost"
#define SENDPORT 12346


//カメ
class Scene4 : public itg::ofxState<SharedData>{
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
    
    float palmPosX[5];
    float palmPosY[5];

    
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
    
    string getName();
    
    ofxTrueTypeFontUC  cat;
    float i1X, i1Y, i2X, i2Y, i3X, i3Y, i4X, i4Y;
    
    Boolean instDone;
    
    ofxOscSender sender;
    int kosuri;
    int tartle;
    
    //バクテリア
    Bacteria bacteria[2];
    
    //水
    ofImage water;
};