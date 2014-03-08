//
//  Scene3.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#include "Scene3.h"

void Scene3::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    inst.loadFont("MTLmr3m.ttf", 24);
	inst.setLineHeight(10.0f);
	inst.setLetterSpacing(1.0);
    
    float tx1 = inst.stringWidth("おやゆびのあいだにも");
    float ty1 = inst.stringHeight("おやゆびのあいだにも");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = inst.stringWidth("バイキンがいっぱい！");
    float ty2 = inst.stringHeight("バイキンがいっぱい！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = inst.stringWidth("おさかなのポーズで");
    float ty3 = inst.stringHeight("おさかなのポーズで");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = inst.stringWidth("あらってみよう！");
    float ty4 = inst.stringHeight("あらってみよう！");
    i4X = ofGetWidth() / 2 - tx4 / 2;
    i4Y = ofGetHeight() / 2 +  ty4 / 2;

    
    // Initial Allocation
    //
    fluid.allocate(ofGetWidth(), ofGetHeight(), 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    fluid.setGravity(ofVec2f(0.0,0.0));
    //  Set obstacle
    //
    fluid.setUseObstacles(false);
    
    // Adding constant forces
    ofSetWindowShape(ofGetWidth(), ofGetHeight());
    
    //指の座標の初期化
    for(int i=0;i<10;i++){
        fingerPosX[i] = 0;
        fingerPosY[i] = 0;
    }
    
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
    fogDensity = 3.0f;
    
	mouseX = 0;
	mouseY = 0;
}

void Scene3::stateEnter(){
    getSharedData().vidGrabber.setDeviceID(0);
	getSharedData().vidGrabber.setDesiredFrameRate(60);
	getSharedData().vidGrabber.initGrabber(camWidth,camHeight);
}

void Scene3::stateExit(){
    getSharedData().vidGrabber.close();
}

void Scene3::update(){
    
//    printf("SharedData x0:%d, y0:%d, scene:%d\n", getSharedData().palmPosX[0], getSharedData().palmPosY[0],getSharedData().scene);
    palmPosX[0] = getSharedData().palmPosX[0];
    palmPosY[0] = getSharedData().palmPosY[0];
    
    // Adding temporal Force
    ofPoint m = ofPoint(palmPosX[0], palmPosY[0]);
    //    ofPoint m = ofPoint(mouseX, mouseY);
    ofPoint d = (m - oldM)*10.0;
    oldM = m;
    ofPoint c = ofPoint(ofGetWidth()/2, ofGetHeight()/2) - m;
    c.normalize();
    //紫
    //    fluid.addTemporalForce(m, d, ofFloatColor(100,70,255), fogDensity);
    //青
    fluid.addTemporalForce(m, d, ofFloatColor(10,70,255), fogDensity);
    
    //  Update
    //
    getSharedData().vidGrabber.update();
    fluid.update();
    
}

void Scene3::draw(){
    ofEnableAlphaBlending();
    getSharedData().vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    fluid.draw();
    ofDisableAlphaBlending();
    
    inst.drawString("おやゆびのあいだにも", i1X, i1Y-300);
    inst.drawString("バイキンがいっぱい！", i2X, i2Y-250);
    inst.drawString("おさかなのポーズで", i3X, i3Y);
    inst.drawString("あらってみよう！", i4X, i4Y+50);
}

void Scene3::keyPressed  (int key){
    switch(key) {
        case 'r':
            if(instDone){
                instDone = false;
            }else{
                instDone = true;
            }
            break;
            
        case 'o':
            vidGrabber.update();
            camWidth = ofGetWidth();
            camHeight = ofGetHeight();
            break;
    }

}

void Scene3::mousePressed(int x, int y, int button){

}

void Scene3::mouseReleased(int x, int y, int button){

 }

//--------------------------------------------------------------
void Scene3::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
    //    printf("mouseX:%d", mouseX);
}

void Scene3::mouseDragged(int x, int y, int button) {

}

void Scene3::windowResized(int w, int h){
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
}

string Scene3::getName(){
    return "Scene3";
}