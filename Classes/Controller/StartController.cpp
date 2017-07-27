//
//  StartController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "StartController.h"
#include "ImageButton.h"
#include "ChessboardProtocol.h"
#include "GameScene.h"
#include "AIGameScene.h"
#include "FixTimeAIGameScene.h"
#include "FixMoveAIGameScene.h"
#include "Message.h"

bool StartController::init(){
    if (! BaseController::init()) {
        return false;
    }
    
    
    // load res
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    Sprite* four_logo = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("four_logo.png"));
    four_logo->setPosition(Vec2(320, 960));
    this->addChild(four_logo);

    Sprite* h2h = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("h2h.png"));
    ImageButton* h2hButton = ImageButton::create(h2h, this, menu_selector(StartController::onH2H));
    h2hButton->setPosition(LogicToReal(Vec2(1, 2)));

    
    
    Sprite* h2c = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("h2c.png"));
    ImageButton* h2cButton = ImageButton::create(h2c, this, menu_selector(StartController::onH2C));
    h2cButton->setPosition(LogicToReal(Vec2(2, 2)));
    
    Sprite* fixTime = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("help.png"));
    ImageButton* fixTimeButton = ImageButton::create(fixTime, this, menu_selector(StartController::onFixTime));
    fixTimeButton->setPosition(LogicToReal(Vec2(1, 1)));
    
    Sprite* fixMove = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("exit.png"));
    ImageButton* fixMoveButton = ImageButton::create(fixMove, this, menu_selector(StartController::onFixMove));
    fixMoveButton->setPosition(LogicToReal(Vec2(2, 1)));
    
    Menu* menu = Menu::create(h2hButton, h2cButton, fixTimeButton, fixMoveButton, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);
    
    return true;
}

void transfer2NextScene(Scene* scene){
    __NotificationCenter::getInstance()->postNotification(CLICK_MSG);
    TransitionSlideInR* slide = TransitionSlideInR::create(0.3, scene);
    Director::getInstance()->replaceScene(slide);
}

void StartController::onH2H(Ref* o){
    Scene* gs = GameScene::create();
    transfer2NextScene(gs);
}

void StartController::onH2C(Ref* o){
    Scene* gs = AIGameScene::create();
    transfer2NextScene(gs);
}

void StartController::onFixTime(Ref* o){
    Scene* gs = FixTimeAIGameScene::create();
    transfer2NextScene(gs);
}

void StartController::onFixMove(Ref* o){
    Scene* gs = FixMoveAIGameScene::create();
    transfer2NextScene(gs);
}

