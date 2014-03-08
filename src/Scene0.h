//
//  Scene0.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/03/05.
//
//

#ifndef __leapTest__Scene0__
#define __leapTest__Scene0__
#include <iostream>
#include "ofxState.h"
#include "SharedData.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxOsc.h"

//#define SENDIP "157.82.5.78"
#define SENDIP "localhost"
#define SENDPORT 12346

#endif /* defined(__leapTest__Scene0__) */

//ただの鏡
class Scene0 : public itg::ofxState<SharedData>{
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

    
    /*
    ofVideoGrabber vidGrabber;
    
    int camWidth;
    int camHeight;
    */
     
    string getName();
    
    Boolean onHuman;
    
    //フォント
    ofxTrueTypeFontUC  title;
    ofxTrueTypeFontUC subTitle;
    
    float titleX, titleY;
    float subTitleX1, subTitleY1, subTitleX2, subTitleY2;
    ofSoundPlayer sceneChangeSound;
    Boolean soundPlayed;
    
    //OSC
    ofxOscSender sender;
    float nextChecker;
    
    ofImage backImage;
    
    int checkCounter;

};