//
//  HelpScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#include "HelpScene.h"
#include "HelpController.h"


bool HelpScene::init(){
    Scene::create();
    
    Layer* layer = HelpController::create();
    this->addChild(layer);
    
    return true;
}
