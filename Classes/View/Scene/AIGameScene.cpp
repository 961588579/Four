//
//  AIGameScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIGameScene.h"
#include "AIChessboardController.h"
#include "MenuController.h"

bool AIGameScene::init(){
    Scene::init();
    
    Layer* cc = AIChessboardController::create();
    this->addChild(cc);
    Layer* mc = MenuController::create();
    this->addChild(mc);
    
    return true;
}
