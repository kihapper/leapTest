//
//  Scene4.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#include "Scene4.h"

void Scene4::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    cat.loadFont("MTLmr3m.ttf", 24);
    cat.setLineHeight(12.0f);
	cat.setLetterSpacing(1.0);
    
    float tx1 = cat.stringWidth("つめのあいだにも");
    float ty1 = cat.stringHeight("つめのあいだにも");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = cat.stringWidth("バイキンがいっぱい！");
    float ty2 = cat.stringHeight("バイキンがいっぱい！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = cat.stringWidth("ねこのポーズで");
    float ty3 = cat.stringHeight("ねこのポーズで");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = cat.stringWidth("あらってみよう！");
    float ty4 = cat.stringHeight("あらってみよう！");
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
    fogDensity = 5.0f;
    
	mouseX = 0;
	mouseY = 0;
}

void Scene4::stateEnter(){
    getSharedData().vidGrabber.setDeviceID(0);
	getSharedData().vidGrabber.setDesiredFrameRate(60);
	getSharedData().vidGrabber.initGrabber(camWidth,camHeight);
}

void Scene4::stateExit(){
    getSharedData().vidGrabber.close();
}

void Scene4::update(){
    
    printf("SharedData x0:%d, y0:%d, scene:%d\n", getSharedData().fingerPosX[0], getSharedData().fingerPosY[0],getSharedData().scene);
    fingerPosX[0] = getSharedData().fingerPosX[0];
    fingerPosY[0] = getSharedData().fingerPosY[0];
    
    // Adding temporal Force
    ofPoint m = ofPoint(fingerPosX[0], fingerPosY[0]);
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

void Scene4::draw(){
    getSharedData().vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    fluid.draw();
    
    
    //これを消さないとバグる
    //GIF
    //    if(hoge < 4){
    //        hoge++;
    //    }else{
    //        hoge=0;
    //    }
    //    testImage[hoge].draw(mouseX, mouseY, testImage[0].getWidth(), testImage[0].getHeight());
    //    ofDrawBitmapString("Scene4 framerate:" + ofToString(ofGetFrameRate()), 30, ofGetHeight() - 30);
    
    cat.drawString("つめのあいだにも", i1X, i1Y-300);
    cat.drawString("バイキンがいっぱい！", i2X, i2Y-250);
    cat.drawString("ねこのポーズで", i3X, i3Y);
    cat.drawString("あらってみよう！", i4X, i4Y+50);
    
}

void Scene4::keyPressed  (int key){
    switch(key) {
        case 'k':
            if(instDone){
                instDone = false;
            }else{
                instDone = true;
            }
            
            vidGrabber.update();
            camWidth = ofGetWidth();
            camHeight = ofGetHeight();
            break;

        default:
            break;
    }
    
}

void Scene4::mousePressed(int x, int y, int button){
    
}

void Scene4::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Scene4::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
    //    printf("mouseX:%d", mouseX);
}

void Scene4::mouseDragged(int x, int y, int button) {
    
}

void Scene4::windowResized(int w, int h){
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
    float tx1 = cat.stringWidth("ゆびのあいだにも");
    float ty1 = cat.stringHeight("ゆびのあいだにも");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = cat.stringWidth("バイキンがいっぱい！");
    float ty2 = cat.stringHeight("バイキンがいっぱい！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = cat.stringWidth("ねこのポーズで");
    float ty3 = cat.stringHeight("ねこのポーズで");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = cat.stringWidth("あらってみよう！");
    float ty4 = cat.stringHeight("あらってみよう！");
    i4X = ofGetWidth() / 2 - tx4 / 2;
    i4Y = ofGetHeight() / 2 +  ty4 / 2;
}

string Scene4::getName(){
    return "Scene4";
}