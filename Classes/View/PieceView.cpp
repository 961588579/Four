//
//  PieceView.cpp
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#include "PieceView.h"
#include "ChessboardProtocol.h"
#include "Chessboard.h"

#include <algorithm>
#include <vector>

PieceView::~PieceView(){
    __NotificationCenter::getInstance()->removeAllObservers(this);
    CC_SAFE_DELETE(this->dropAction);
    CC_SAFE_RELEASE(this->model);
}

bool PieceView::init(){
    Sprite::init();
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PieceView::onBeginMove), BEGIN_MOVE_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PieceView::onBeginEat), BEGIN_EAT_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PieceView::onRegret), REGRET_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PieceView::onAIRegret), AI_REGRET_MSG, nullptr);
    
    return true;
}

PieceView* PieceView::create(const Move* _currentMove, Model* _model, cocos2d::SpriteFrame *frame, const Vec2& _logic_position){
    PieceView* view = PieceView::create();
    view->setCurrentMove(_currentMove);
    view->setModel(_model);
    _model->retain();
    view->setDisplayFrame(frame);
    Vec2 dest = LogicToReal(_logic_position);
    view->setPosition(Vec2(dest.x, Director::getInstance()->getVisibleSize().height));
    ActionInterval* drop = MoveTo::create(0.6f, dest);

    drop->retain();
    view->setDropAction(drop);
    
    return view;
}

void PieceView::onEnter(){
    Sprite::onEnter();
    ActionInterval* bounce = EaseBounceOut::create(this->dropAction);
    this->runAction(bounce);
    __NotificationCenter::getInstance()->postNotification(CREATE_MSG);
}

void PieceView::onExit(){
    //this->runAction(dropAction->reverse());
    Sprite::onExit();
}


void PieceView::onBeginMove(Ref* o){
    if (!(currentMove->src).equals(RealToLogic(this->getPosition())))
        return;
    Vec2 dest = LogicToReal(currentMove->dest);
    model->waitAction(this, EaseExponentialOut::create(MoveTo::create(0.5f, dest)), END_MOVE_MSG);
}

void PieceView::onBeginEat(Ref* o){
    const std::vector<Vec2> eatenPoints = currentMove->eatenPoints;
    Vec2 logic_position = RealToLogic(this->getPosition());
    
    
    if (std::find_if(eatenPoints.begin(), eatenPoints.end(),
                     [logic_position](const Vec2& p)->bool{return p.equals(logic_position) ;} ) == eatenPoints.end())
//    if (!eatenPoints[0].equals(logic_position))
        return;
    ScaleTo* st = ScaleTo::create(0.2f, 0.05);
    RemoveSelf* rs = RemoveSelf::create();
    model->waitAction(this, Sequence::createWithTwoActions(st, rs), END_EAT_MSG);
}

void PieceView::onRegret(Ref* o){
    if (!(currentMove->dest).equals(RealToLogic(this->getPosition())))
        return;
    Vec2 src = LogicToReal(currentMove->src);
    model->waitAction(this, EaseExponentialOut::create(MoveTo::create(0.6f, src)), END_MOVE_MSG);
}

void PieceView::onAIRegret(Ref* o){
    if (!(currentMove->dest).equals(RealToLogic(this->getPosition())))
        return;
    Vec2 src = LogicToReal(currentMove->src);
    model->waitAction(this, EaseExponentialOut::create(MoveTo::create(0.65f, src)), AI_END_MOVE_MSG);
}



