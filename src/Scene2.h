//
//  Scene2.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.

#ifndef __leapTest__Scene2__
#define __leapTest__Scene2__

#include <iostream>
#include "ofxState.h"
#include "SharedData.h"
#include "ofxFluid.h"
#include "ofxOsc.h"
#include "ofxTrueTypeFontUC.h"

#include "Bacteria.h"

#define SENDIP "localhost"
#define SENDPORT 12346

#define PALMDIST 120
#define PORT 12345
#define NUM_MSG_STRINGS 20
#define OFFSETX 0
#define OFFSETY -100

#endif /* defined(__leapTest__Scene2__) */

//普通の手洗い
class Scene2 : public itg::ofxState<SharedData>{
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
    int mouseX, mouseY;
    
    //ウェブカム映像のハンドリング
    //ofVideoGrabber vidGrabber;
    //int camWidth;
    //int camHeight;
        
    //testGIF
    ofImage testImage[5];
    char gifTest[5];
    
    //フォント
    ofxTrueTypeFontUC  iFont;
    ofxTrueTypeFontUC  iFont_m;

    float i1X, i1Y, i2X, i2Y, i3X, i3Y, i4X, i4Y;
    
    Boolean GIF;
    int hoge;
    
    Boolean setGesture;
    string getName();
    
    ofxOscSender sender;
    int kosuri;
    
    //バクテリア
    Bacteria bacteria[2];
    
    //水
    ofImage water;


};