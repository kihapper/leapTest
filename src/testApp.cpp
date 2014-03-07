#include "testApp.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"


//--------------------------------------------------------------
void testApp::setup(){
    stateMachine.addState<Scene0>();
    stateMachine.addState<Scene1>();
    stateMachine.addState<Scene2>();
    stateMachine.addState<Scene3>();
    stateMachine.addState<Scene4>();
    stateMachine.addState<Scene5>();
    
    ofSetFrameRate(24);
    
    stateMachine.changeState("Scene0");
    stageState = 0;
    
    //initialize coodination
    for(int i=0;i<10;i++){
        stateMachine.getSharedData().fingerPosX[i] = 0;
    }
    for(int j=0;j<10;j++){
        stateMachine.getSharedData().fingerPosY[j] = 0;
    }
    
    cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    
    onHuman = false;
    stateMachine.getSharedData().onHuman = onHuman;
    
    BGMSound.loadSound("sound/test.wav");
    BGMSound.setLoop(true);
    BGMSound.setVolume(0.6);
    BGMSound.play();
    
    stateMachine.getSharedData().elapsedTime = elapsedTime;
}

//--------------------------------------------------------------
void testApp::update(){
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        //fingerPos from OSC
		if(m.getAddress() == "/leap/fingerPosition"){
			// both the arguments are int32's
			mouseX = m.getArgAsInt32(0);
            mouseY = m.getArgAsInt32(1);
            stateMachine.getSharedData().fingerPosX[0] = mouseX;
            stateMachine.getSharedData().fingerPosY[0] = mouseY;
//            printf("fingerX:%d fingerY:%d\n",stateMachine.getSharedData().fingerPosX[0],stateMachine.getSharedData().fingerPosY[0]);
		}
        
		//Scene from OSC
		else if(m.getAddress() == "/leap/scene"){
            stateMachine.getSharedData().scene = m.getArgAsInt32(0);
//            printf("scene:%d\n",m.getArgAsInt32(0));
            stageChange(stateMachine.getSharedData().scene);
        }
        
        //gesture from OSC
        else if(m.getAddress() == "/leap/gesture"){
            stateMachine.getSharedData().gesture = m.getArgAsInt32(0);
//            printf("gesture:%d\n",m.getArgAsInt32(0));
		}
        
        //onHuman flag from OSC
        else if(m.getAddress() == "/leap/onHuman"){
            stateMachine.getSharedData().onHuman = m.getArgAsInt32(0);
//            printf("onHuman:%d", m.getArgAsInt32(0));
        }
        
        //pomp flag from OSC
        else if(m.getAddress() == "/leap/pushed"){
            stateMachine.getSharedData().pushed = m.getArgAsInt32(0);
//            printf("pushed:%d", m.getArgAsInt32(0));
        }
        
        else if (m.getAddress() == "/leap/kosuri"){
            stateMachine.getSharedData().kosuri = m.getArgAsInt32(0);
//            printf("kosuri:%d", m.getArgAsInt32(0));
        }
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
}

void testApp::stageChange(int stageState){
    switch (stageState) {
        case 0:
            stateMachine.changeState("Scene0");
            break;
            
        case 1:
            stateMachine.changeState("Scene1");
            break;

        case 2:
            stateMachine.changeState("Scene2");
            break;
            
        case 3:
            stateMachine.changeState("Scene3");
            break;
            
        case 4:
            stateMachine.changeState("Scene4");
            break;
            
        case 5:
            stateMachine.changeState("Scene5");
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'f'){
        ofToggleFullscreen();
    }
    if(key == 'n'){
        if(stageState<5){
            stageState++;
        }else{
            stageState = 0;
        }
    }
    if(key == 'h'){
        if(onHuman){
            onHuman = false;
        }else{
            onHuman = true;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
}