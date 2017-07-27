//
//  TimeBoard.cpp
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#include "TimeBoard.h"
#include "Message.h"

bool TimeBoard::init(){
    
    leftSeconds = 60;
    Label::initWithTTF("Time : 60", "Helvetica-Bold", 32.0f);
    this->setColor(Color3B::BLACK);
    this->setPosition(Vec2(320, 860));
    
    return true;
}

void TimeBoard::onEnter(){
    Label::onEnter();
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TimeBoard::onStop), WIN_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TimeBoard::onStop), LOSE_MSG, nullptr);
    this->schedule(schedule_selector(TimeBoard::onTimeChanged), 1.0f);
}

void TimeBoard::onExit(){
    Label::onExit();
    __NotificationCenter::getInstance()->removeAllObservers(this);
    this->unscheduleAllSelectors();
}

void TimeBoard::onTimeChanged(float dt){
    leftSeconds--;
    CCString* str = CCString::createWithFormat("Time : %d", leftSeconds);
    this->setString(str->getCString());
    if (leftSeconds == 0) {
        __NotificationCenter::getInstance()->postNotification(LOSE_MSG);
    }
}

void TimeBoard::onStop(Ref *ref){
    this->unscheduleAllSelectors();
}

