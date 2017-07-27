//
//  FixMoveAIGameScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#include "FixMoveAIGameScene.h"
#include "FixMoveAIChessboardController.h"
#include "MenuController.h"

bool FixMoveAIGameScene::init(){
    
    Layer* l1 = FixMoveAIChessboardController::create();
    this->addChild(l1);
    Layer* l2 = MenuController::create();
    this->addChild(l2);
    
    return true;
}
