//
//  LogoView.cpp
//  Four
//
//  Created by 王选易 on 14-5-3.
//
//

#include "LogoView.h"
#include "Message.h"

LogoView::~LogoView(){
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

bool LogoView::init(){
    Sprite::init();
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LogoView::onNextRound), NEXT_ROUND_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LogoView::onNextRound), REGRET_MSG, nullptr);
    
    return true;
}

LogoView* LogoView::create(const Move *_currentMove, cocos2d::SpriteFrame *frame, PIECE _presentRound){
    LogoView* view = LogoView::create();
    view->setDisplayFrame(frame);
    view->setCurrentMove(_currentMove);
    view->setPresentRound(_presentRound);
    return view;
}

void LogoView::onEnter(){
    Sprite::onEnter();
    this->setPosition(Vec2(832, 960));
    if (this->presentRound == this->currentMove->currentRound ){
        this->onNextRound(nullptr);
    }
}

void LogoView::onNextRound(Ref* o){
    if (this->presentRound == this->currentMove->currentRound ) {
        this->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.0f, Vec2(320, 960))));
    }else{
        this->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(0.4f, Vec2(-192, 960)), CCPlace::create(Vec2(832, 960)) ) );
    }
}

void LogoView::activateStop(){
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LogoView::onStop), WIN_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LogoView::onStop), LOSE_MSG, nullptr);
}

void LogoView::onStop(Ref *ref){
    this->runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.05f, 0.5f), CCRemoveSelf::create()));
}
