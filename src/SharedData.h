//
//  SharedData.h
//  leapTest
//
//  Created by Yuta Takeuchi on 2014/02/23.
//
//

#pragma once

//共通して使うデータ
class SharedData{
    public:
    
    int fingerPosX[15];
    int fingerPosY[15];
    
    int palmPosX[5];
    int palmPosY[5];
    
    int scene;
    int gesture;
    int kosuri;
    
    ofVideoGrabber vidGrabber;
    
    float elapsedTime;
    
    Boolean onHuman;
    Boolean pushed;
    
};