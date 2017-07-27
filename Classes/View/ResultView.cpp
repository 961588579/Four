//
//  ResultView.cpp
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#include "ResultView.h"
#include "Message.h"

ResultView::~ResultView(){
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

bool ResultView::init(){
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ResultView::onWin), WIN_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ResultView::onLose), LOSE_MSG, nullptr);
    
    Label::initWithTTF("", "Helvetica-Bold", 96.0f);
    this->setColor(Color3B::BLACK);
    this->setPosition(Vec2(320, 1200));
    
    return true;
}

void ResultView::onWin(Ref* o){
    this->setString("WIN");
    this->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5f, Vec2(320, 960))));
}

void ResultView::onLose(Ref* o){
    this->setString("LOSE");
    this->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5f, Vec2(320, 960))));
}
