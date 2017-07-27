//
//  MoveBoard.cpp
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#include "MoveBoard.h"
#include "Message.h"
#include "Chessboard.h"

bool MoveBoard::init(){
    
    leftMoves = 30;
    Label::initWithTTF("Move : 30", "Helvetica-Bold", 32.0f);
    this->setColor(Color3B::BLACK);
    this->setPosition(Vec2(320, 860));
    
    return true;
}

void MoveBoard::onEnter(){
    Label::onEnter();
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MoveBoard::onNextRound), NEXT_ROUND_MSG, NULL);
}

void MoveBoard::onExit(){
    Label::onExit();
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

void MoveBoard::onNextRound(cocos2d::Ref *o){
    Chessboard* chessboard = dynamic_cast<Chessboard*>(o);
    if (chessboard->getCurrentMove().currentRound == BLACK){
        leftMoves--;
        __String* str = __String::createWithFormat("Move : %d", leftMoves);
        this->setString(str->getCString());
        if (leftMoves == 0) {
            __NotificationCenter::getInstance()->postNotification(LOSE_MSG);
        }
    }
}


