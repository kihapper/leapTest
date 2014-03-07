//
//  Scene0.cpp
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/03/05.
//
//

#include "Scene0.h"

void Scene0::setup() {
    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
    //    //フォント
    title.loadFont("MTLmr3m.ttf", 36);
	title.setLineHeight(18.0f);
	title.setLetterSpacing(1.0);
    
    subTitle.loadFont("MTLmr3m.ttf", 24);
	subTitle.setLineHeight(12.0f);
	subTitle.setLetterSpacing(1.0);
    
    float tx1 = title.stringWidth("てあらいかがみ");
    float ty1 = title.stringHeight("てあらいかがみ");
    titleX = ofGetWidth() / 2 - tx1 / 2;
    titleY = ofGetHeight() / 2 +  ty1 / 2;
    
    
    float tx2 = subTitle.stringWidth("どうぶつといっしょに");
    float ty2 = subTitle.stringHeight("どうぶつといっしょに");
    subTitleX1 = ofGetWidth() / 2 - tx2 / 2;
    subTitleY1 = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = subTitle.stringWidth("手をあらおう！");
    float ty3 = subTitle.stringHeight("手をあらおう！");
    subTitleX2 = ofGetWidth() / 2 - tx3 / 2;
    subTitleY2 = ofGetHeight() / 2 +  ty3 / 2;
    
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
	getSharedData().vidGrabber.setDesiredFrameRate(60);
    getSharedData().vidGrabber.setVerbose(true);
    
    //人の判定
    
    sceneChangeSound.loadSound("sound/sceneChange.mp3");
    sceneChangeSound.setVolume(0.8);
    
    sender.setup(SENDIP, SENDPORT);
}

void Scene0::stateEnter(){
	getSharedData().vidGrabber.setDeviceID(0);
	getSharedData().vidGrabber.initGrabber(camWidth,camHeight);
    soundPlayed = false;
    nextChecker = 3600.0f*3;
    onHuman = false;
    testCounter = 0;
}

void Scene0::stateExit(){
    getSharedData().vidGrabber.close();
    onHuman = false;
}


void Scene0::update() {
    printf("%f\n", ofGetElapsedTimef());
    getSharedData().vidGrabber.update();
    if(getSharedData().onHuman == true){
        onHuman = true;
        
    }
    if(onHuman){
        testCounter++;
        if(testCounter < 10){
            ofResetElapsedTimeCounter();
        }
        if(ofGetElapsedTimef() > 5.0f){
            ofxOscMessage sendReset;
            sendReset.setAddress("/leap/sendReset");
            sendReset.addIntArg(1);
            sender.sendMessage(sendReset);
            printf("sendReset");
        }
        if(soundPlayed == false){
            sceneChangeSound.play();
            soundPlayed = true;
        }
    }
//        printf("nextChecker:%f", nextChecker);
 
}

void Scene0::draw() {
    // camera
    getSharedData().vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    if(onHuman){
        ofSetColor(255);
        title.drawString("てあらいかがみ", titleX, titleY-60);
        subTitle.drawString("どうぶつといっしょに", subTitleX1, subTitleY1);
        subTitle.drawString("手をあらおう！", subTitleX2, subTitleY2+40);
    }
    ofDrawBitmapString("scene0 framerate:" + ofToString(ofGetFrameRate()), 30, ofGetHeight() - 30);
}

void Scene0::keyPressed(int key){
    if(key == 'p'){
        //arduinoに変更
        if(onHuman == true){
            onHuman = false;
//            getSharedData().onHuman = onHuman;

        }else{
            onHuman = true;
//            getSharedData().onHuman = onHuman;
            nextChecker = ofGetElapsedTimef();
        }
    }
    if(key == 's'){
        if(soundPlayed){
            soundPlayed = false;
        }else{
            soundPlayed = true;
        }
    }
}

void Scene0::mouseMoved(int x, int y ){
    
}

void Scene0::mouseDragged(int x, int y, int button){
    
}

void Scene0::mousePressed(int x, int y, int button){
    onHuman = true;
}

void Scene0::mouseReleased(int x, int y, int button){
    onHuman = false;
}

void Scene0::windowResized(int w, int h){
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
    float tx1 = title.stringWidth("てあらいかがみ");
    float ty1 = title.stringHeight("てあらいかがみ");
    titleX = ofGetWidth() / 2 - tx1 / 2;
    titleY = ofGetHeight() / 2 +  ty1 / 2;
    
    
    float tx2 = subTitle.stringWidth("どうぶつといっしょに");
    float ty2 = subTitle.stringHeight("どうぶつといっしょに");
    subTitleX1 = ofGetWidth() / 2 - tx2 / 2;
    subTitleY1 = ofGetHeight() / 2 +  ty2 / 2;
    
    float tx3 = subTitle.stringWidth("手をあらおう！");
    float ty3 = subTitle.stringHeight("手をあらおう！");
    subTitleX2 = ofGetWidth() / 2 - tx3 / 2;
    subTitleY2 = ofGetHeight() / 2 +  ty3 / 2;

}


string Scene0::getName(){
    return "Scene0";
}