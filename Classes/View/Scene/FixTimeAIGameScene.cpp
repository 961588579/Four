//
//  FixTimeAIGameScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#include "FixTimeAIGameScene.h"
#include "FixTimeAIChessboardController.h"
#include "MenuController.h"

bool FixTimeAIGameScene::init(){
    
    Layer* l1 = FixTimeAIChessboardController::create();
    this->addChild(l1);
    Layer* l2 = MenuController::create();
    this->addChild(l2);
    
    return true;
}

