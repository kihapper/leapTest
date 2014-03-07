#pragma once

#include "ofMain.h"
#include "Leap.h"
#include "ofxStateMachine.h"
#include "SharedData.h"
#include "ofxOsc.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    itg::ofxStateMachine<SharedData> stateMachine;
    
    int stageState;
    int stageCheck;
    void stageChange(int stageState);
    
    //OSC
    ofxOscReceiver receiver;
    
    int fingerPosX[25];
    int fingerPosY[25];
    
    int palmPosX[15];
    int palmPosY[15];
    
    float elapsedTime;
    
    int gesture;
    
    Boolean onHuman;
    ofSoundPlayer BGMSound;
};