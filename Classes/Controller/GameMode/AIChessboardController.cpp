//
//  AIChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIChessboardController.h"
#include "AIController.h"
#include "Message.h"
#include "Chessboard.h"
#include "PieceView.h"
#include "LogoView.h"
#include "Tag.h"
#include "ResultView.h"
#include "RotFlowerParticle.h"

AIChessboardController::~AIChessboardController(){
    CC_SAFE_RELEASE(actor);
}

bool AIChessboardController::init(){
    ChessboardController::init();
    
    actor = AIController::create();
    actor->retain();
    
    LogoView* black = dynamic_cast<LogoView*>(this->getChildByTag(ROUND_BLACK));
    LogoView* white = dynamic_cast<LogoView*>(this->getChildByTag(ROUND_WHITE));
    
    black->activateStop();
    white->activateStop();
    
    Label* label = ResultView::create();
    this->addChild(label);
    
    modeLabel->setString("人机对战");
    
    return true;
}

void AIChessboardController::onEnter(){
    ChessboardController::onEnter();
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(AIChessboardController::onNextRound), NEXT_ROUND_MSG, nullptr);
    __NotificationCenter::getInstance()->removeObserver(this, CLICK_REGRET_MSG);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(AIChessboardController::tryRegret), AI_END_MOVE_MSG, nullptr);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(AIChessboardController::tryAIRegret), CLICK_REGRET_MSG, nullptr);
}

void AIChessboardController::onExit(){
    ChessboardController::onExit();
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

void AIChessboardController::onNextRound(Ref* o){
    if (chessboard->getCurrentMove().currentRound == AI ) {
        Move move(AI);
        actor->getNextMove(chessboard->getPieces(), move);
        this->tryMove(move.src, move.dest);
    }else {
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(BaseController::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(BaseController::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(BaseController::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    }
}

void AIChessboardController::tryAIRegret(Ref *o){
    if (chessboard->checkMessage(REGRET_MSG)){
        chessboard->alterAIRegret();
        
        CCString* frame_name = ( chessboard->getCurrentMove().currentRound == WHITE ) ? CCString::create("black.png") : CCString::create("white.png");
        
        for (CCPoint p : chessboard->getCurrentMove().eatenPoints) {
            CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCSprite* piece = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), p);
            this->addChild(piece);
        }
    }
}

void AIChessboardController::tryWin(Ref* o){
    if (chessboard->checkMessage(WIN_MSG)) {
        if (chessboard->checkWin(chessboard->getCurrentMove()) &&  chessboard->getCurrentMove().currentRound == PLAYER){
            chessboard->alterWin();
            this->addChild(RotFlowerParticle::create());
        }else if (chessboard->checkWin(chessboard->getCurrentMove()) &&  chessboard->getCurrentMove().currentRound == AI) {
            chessboard->alterLose();
        }else{
            chessboard->alterNextRound();
        }
    }
}
