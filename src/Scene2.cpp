//
//  Scene2.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#include "Scene2.h"

void Scene2::setup(){
    hoge=0;
    ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    iFont_m.loadFont("MTLmr3m.ttf", 24);
	iFont_m.setLineHeight(10.0f);
	iFont_m.setLetterSpacing(1.0);
    
    float tx1 = iFont_m.stringWidth("あらいぐまのポーズで");
    float ty1 = iFont_m.stringHeight("あらいぐまのポーズで");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = iFont_m.stringWidth("手をあらおう！");
    float ty2 = iFont_m.stringHeight("手をあらおう！");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = iFont_m.stringWidth("手のひらを合わせて");
    float ty3 = iFont_m.stringHeight("手のひらを合わせて");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    float tx4 = iFont_m.stringWidth("スリスリ");
    float ty4 = iFont_m.stringHeight("スリスリ");
    i4X = ofGetWidth() / 2 - tx4 / 2;
    i4Y = ofGetHeight() / 2 +  ty4 / 2;
    
    for(int i=0; i<5; i++){
        sprintf(gifTest,"test/gif%d.png",i);
        testImage[i].loadImage(gifTest);
        testImage[i].loadImage(gifTest);
    }
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
    
    //initialize parameters
    fogDensity = 5.0f;
    
	mouseX = 0;
	mouseY = 0;
}

void Scene2::stateEnter(){
    getSharedData().vidGrabber.setDeviceID(0);
	getSharedData().vidGrabber.setDesiredFrameRate(60);
	getSharedData().vidGrabber.initGrabber(camWidth,camHeight);
}

void Scene2::stateExit(){
    getSharedData().vidGrabber.close();
    
}


void Scene2::update(){
    //人がいなくなったら、0に戻る処理も必要
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
    fluid.addTemporalForce(m, d, ofFloatColor(10,70,255)*0.1, fogDensity);
    
    //  Update
    getSharedData().vidGrabber.update();
    fluid.update();
}


void Scene2::draw(){
    ofEnableAlphaBlending();
    getSharedData().vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    fluid.draw();
    //これを消さないとバグる
    //GIF
    if(hoge < 4){
        hoge++;
    }else{
        hoge=0;
    }
    testImage[hoge].draw(fingerPosY[0], fingerPosY[0], testImage[0].getWidth(), testImage[0].getHeight());
    ofDisableAlphaBlending();
    
    if(setGesture){
        iFont_m.drawString("あらいぐまのポーズで", i1X, i1Y-80);
        iFont_m.drawString("手をあらおう！", i2X, i2Y-40);

        iFont_m.drawString("手のひらを合わせて", i3X, i3Y+40);
        iFont_m.drawString("スリスリ", i4X, i4Y+80);
    }
//    ofDrawBitmapString("Scene2 framerate:" + ofToString(ofGetFrameRate()), 30, ofGetHeight() - 30);
    
}

void Scene2::keyPressed  (int key){
    switch(key) {
        case ',':
            if(setGesture){
                setGesture = false;
            }else{
                setGesture = true;
            }
            break;
            
        case 'r':
            vidGrabber.update();
            camWidth = ofGetWidth();
            camHeight = ofGetHeight();
            break;
    }
}

void Scene2::mousePressed(int x, int y, int button){
    GIF = true;
}

void Scene2::mouseReleased(int x, int y, int button){
    GIF = false;
}

//--------------------------------------------------------------
void Scene2::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
//    printf("mouseX:%d", mouseX);
}

void Scene2::mouseDragged(int x, int y, int button) {

}

void Scene2::windowResized(int w, int h){
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
}

string Scene2::getName(){
    return "Scene2";
}

