//
//  Scene1.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#include "Scene1.h"

void Scene1::setup() {
    
    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    
    //フォント
    iFont.loadFont("MTLmr3m.ttf", 24);
	iFont.setLineHeight(12.0f);
	iFont.setLetterSpacing(1.0);
    
    float tx1 = iFont.stringWidth("手をだしてみよう！");
    float ty1 = iFont.stringHeight("手をだしてみよう！");
    i1X = ofGetWidth() / 2 - tx1 / 2;
    i1Y = ofGetHeight() / 2 +  ty1 / 2;
    
    float tx2 = iFont.stringWidth("よごれている手を");
    float ty2 = iFont.stringHeight("よごれている手を");
    i2X = ofGetWidth() / 2 - tx2 / 2;
    i2Y = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = iFont.stringWidth("ジェルであらおう！");
    float ty3 = iFont.stringHeight("ジェルであらおう！");
    i3X = ofGetWidth() / 2 - tx3 / 2;
    i3Y = ofGetHeight() / 2 +  ty3 / 2;
    
    /*
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
     vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    //ウェブカメラ
	getSharedData().vidGrabber.setDesiredFrameRate(24);
    getSharedData().vidGrabber.setVerbose(true);
    */
     
    //人の判定
    onHuman = false;
    
    //手のフラグ
    setHand = false;
    sender.setup(SENDIP, SENDPORT);
    
    
    //バクテリア
    bacteria[0].reset();
    bacteria[1].reset();
    
    //水
    water.loadImage("image/water.png");

}

void Scene1::stateEnter(){
//	
    if (getSharedData().vidGrabber.listDevices().size() > 1 ){
        
        getSharedData().vidGrabber.setDeviceID(1);
        getSharedData().vidGrabber.initGrabber(getSharedData().camWidth, getSharedData().camHeight);
        
        
    } else {
        getSharedData().vidGrabber.setDeviceID(0);
        getSharedData().vidGrabber.initGrabber(getSharedData().camWidth, getSharedData().camHeight);
    }
    
    setHand = false;
    ofResetElapsedTimeCounter();
}

void Scene1::stateExit(){
    getSharedData().vidGrabber.close();
}


void Scene1::update() {
    getSharedData().vidGrabber.update();
    
    //バクテリアupdate
    bacteria[0].update(true);
    bacteria[1].update(true);
    
}

void Scene1::draw() {
    // camera
    getSharedData().vidGrabber.draw(ofGetWidth() - getSharedData().camPos.x,
                                    getSharedData().camPos.y,
                                    -getSharedData().camWidth * getSharedData().camScale,
                                    getSharedData().camHeight * getSharedData().camScale);
    
    
    //ばい菌
    bacteria[0].draw(getSharedData().palmPosX[0], getSharedData().palmPosY[0]);
    bacteria[1].draw(getSharedData().palmPosX[1], getSharedData().palmPosY[1]);
    
    
    //水
    ofSetColor(255);
    ofEnableAlphaBlending();
    water.draw(0, 0, ofGetWidth(), water.height * ofGetWidth() / water.width );
    ofDisableAlphaBlending();
    
    
    if(getSharedData().setHand){
        setHand = true;
    }
    if(setHand == false){
        iFont.drawString("手をだしてみよう！", i1X, i1Y-300);
    }else{
        iFont.drawString("よごれている手を", i2X, i2Y-300);
        iFont.drawString("ジェルであらおう！", i3X, i3Y-250);
        if(getSharedData().pushed){
//            checkCounter++;
//            if(checkCounter<60){
                ofxOscMessage sendReset;
                sendReset.setAddress("/leap/sendReset");
                sendReset.addIntArg(2);
                sender.sendMessage(sendReset);
                printf("sendReset");
                checkCounter = 0;
//            }
        }
    }
    
    
    
    
    ofSetColor(255);
    ofDrawBitmapString("Scene1 framerate:" + ofToString(ofGetFrameRate()), 30, ofGetHeight() - 30);
}

void Scene1::keyPressed(int key){
    if(key == 'l'){
        if(setHand == true){
            setHand = false;
        }else{
            setHand = true;
        }
    }
}

void Scene1::mouseMoved(int x, int y ){

}

void Scene1::mouseDragged(int x, int y, int button){

}

void Scene1::mousePressed(int x, int y, int button){
    onHuman = true;
}

void Scene1::mouseReleased(int x, int y, int button){
    onHuman = false;
}

void Scene1::windowResized(int w, int h){
    
}


string Scene1::getName(){
    return "Scene1";
}