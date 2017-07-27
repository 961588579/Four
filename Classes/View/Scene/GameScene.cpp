//
//  GameScene.cpp
//  Four
//
//  Created by 王选易 on 14-4-25.
//
//

#include "GameScene.h"
#include "ChessboardController.h"
#include "MenuController.h"

bool GameScene::init(){
    Scene::init();
    
    Layer* cc = ChessboardController::create();
    this->addChild(cc);
    Layer* mc = MenuController::create();
    this->addChild(mc);
    
    return true;
}
