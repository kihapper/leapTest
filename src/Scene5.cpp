//
//  Scene5.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#include "Scene5.h"

void Scene5::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    clearWord.loadFont("MTLmr3m.ttf", 24);
	clearWord.setLineHeight(10.0f);
	clearWord.setLetterSpacing(1.0);
    
    float tx1 = clearWord.stringWidth("OK!");
    float ty1 = clearWord.stringHeight("OK!");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = clearWord.stringWidth("きれいになったね！");
    float ty2 = clearWord.stringHeight("きれいになったね！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = clearWord.stringWidth("正しいてあらいを");
    float ty3 = clearWord.stringHeight("正しいてあらいを");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = clearWord.stringWidth("みんなにもおしえよう！");
    float ty4 = clearWord.stringHeight("みんなにもおしえよう！");
    i4X = ofGetWidth() / 2 - tx4 / 2;
    i4Y = ofGetHeight() / 2 +  ty4 / 2;

    // Initial Allocation
    fluid.allocate(ofGetWidth(), ofGetHeight(), 0.5);
    
    // Seting the gravity set up & injecting the background image
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    fluid.setGravity(ofVec2f(0.0,0.0));
    
    //  Set obstacle
    fluid.setUseObstacles(false);
    
    // Adding constant forces
    ofSetWindowShape(ofGetWidth(), ofGetHeight());
    
    //使えるカメラのリスト化
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    //ビデオの設定
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
    getSharedData().vidGrabber.setDesiredFrameRate(24);
    getSharedData().vidGrabber.setVerbose(true);
    
    //
    //initialize parameters
    fogDensity = 5.0f;
    
	mouseX = 0;
	mouseY = 0;
    
    //OSC
    sender.setup(SENDIP, SENDPORT);
}

void Scene5::stateEnter(){
    getSharedData().vidGrabber.setDeviceID(0);
	getSharedData().vidGrabber.setDesiredFrameRate(60);
	getSharedData().vidGrabber.initGrabber(camWidth,camHeight);
    
    ofResetElapsedTimeCounter();
}

void Scene5::stateExit(){
    getSharedData().vidGrabber.close();
}

void Scene5::update(){
    getSharedData().vidGrabber.update();

    if(ofGetElapsedTimef() > 8.0f){
        //5秒ほど表示したら元に戻る
        //しばらく人が来ても受け付けない処理とかも必要かも
        ofxOscMessage sendReset;
        sendReset.setAddress("/leap/sendReset");
        sendReset.addIntArg(0);
        sender.sendMessage(sendReset);
    }
}

void Scene5::draw(){
    getSharedData().vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    
        clearWord.drawString("OK!", i1X, i1Y-300);
        clearWord.drawString("きれいになったね！", i2X, i2Y-250);
        clearWord.drawString("正しいてあらいを", i3X, i3Y+50);
        clearWord.drawString("みんなにおしえてあげよう！", i4X, i3Y+100);
}

void Scene5::keyPressed  (int key){
    switch(key) {
        case 'r':
            vidGrabber.update();
            camWidth = ofGetWidth();
            camHeight = ofGetHeight();
            break;
            
        case 'm':
            if(nextView){
                nextView = false;
            }else{
                nextView = true;
            }
            break;
    }
    
}

void Scene5::mousePressed(int x, int y, int button){
}

void Scene5::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void Scene5::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
    //    printf("mouseX:%d", mouseX);
}

void Scene5::mouseDragged(int x, int y, int button) {

}

void Scene5::windowResized(int w, int h){
    camWidth = ofGetWidth();	// try to grab at this size.
	camHeight = ofGetHeight();
    
    float tx1 = clearWord.stringWidth("OK!");
    float ty1 = clearWord.stringHeight("OK!");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = clearWord.stringWidth("きれいになったね！");
    float ty2 = clearWord.stringHeight("きれいになったね！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = clearWord.stringWidth("正しいてあらいを");
    float ty3 = clearWord.stringHeight("正しいてあらいを");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = clearWord.stringWidth("みんなにもおしえよう！");
    float ty4 = clearWord.stringHeight("みんなにもおしえよう！");
    i4X = ofGetWidth() / 2 - tx4 / 2;
    i4Y = ofGetHeight() / 2 +  ty4 / 2;

}

string Scene5::getName(){
    return "Scene5";
}