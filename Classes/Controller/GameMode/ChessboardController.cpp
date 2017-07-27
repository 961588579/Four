//
//  ChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#include "ChessboardController.h"
#include "PieceView.h"
#include "LogoView.h"
#include "Chessboard.h"
#include "RotFlowerParticle.h"
#include "ChessboardProtocol.h"
#include "Tag.h"



ChessboardController::~ChessboardController(){
    CC_SAFE_RELEASE(chessboard);
    CC_SAFE_RELEASE(modeLabel);
}

void ChessboardController::initPieceViews(){
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            __String* frame_name;
            if (chessboard->getPiece(Vec2(j, i)) == BLACK )
                frame_name = new __String("black.png");
            else if (chessboard->getPiece(Vec2(j, i)) == WHITE)
                frame_name = new __String("white.png");
            else
                continue;
            Sprite* black = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), Vec2(j, i));
            this->addChild(black);
        }
    }
}

bool ChessboardController::init(){
    using namespace cocos2d;
    
    if (! BaseController::init()) {
        return false;
    }
    
    // 初始化Model
    this->chessboard = Chessboard::create();
    this->chessboard->retain();
    
//    PIECE _pieces[4][4] = {
//        {ZERO, WHITE, ZERO, BLACK},
//        {ZERO, ZERO, WHITE, BLACK},
//        {ZERO, ZERO, ZERO, ZERO},
//        {ZERO, ZERO, ZERO, ZERO}
//    };
    
//    chessboard->setPieces(_pieces);
    
    //初始化View
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    initPieceViews();
    
    Sprite* black_logo = LogoView::create(&(this->chessboard->getCurrentMove()), cache->getSpriteFrameByName("black_logo.png"), BLACK);
    black_logo->setTag(ROUND_BLACK);
    Sprite* white_logo = LogoView::create(&(this->chessboard->getCurrentMove()), cache->getSpriteFrameByName("white_logo.png"), WHITE);
    white_logo->setTag(ROUND_WHITE);
    this->addChild(black_logo);
    this->addChild(white_logo);
    
    modeLabel = Label::createWithTTF("人人对战", "Helvetica-Bold", 32.0f);
    modeLabel->setColor(Color3B::BLACK);
    modeLabel->setPosition(Vec2(320, 1050));
    CC_SAFE_RETAIN(modeLabel);
    this->addChild(modeLabel);

    return true;
}


void ChessboardController::onEnter()
{
    using cocos2d::CCDirector;
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ChessboardController::tryEat), END_MOVE_MSG, NULL);
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ChessboardController::tryWin), END_EAT_MSG, NULL);
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ChessboardController::tryRegret), CLICK_REGRET_MSG, nullptr);
    
//    this->setTouchEnabled(true);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(ChessboardController::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(ChessboardController::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(ChessboardController::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    Layer::onEnter();
}

void ChessboardController::onExit()
{
    using cocos2d::CCDirector;
    
    __NotificationCenter::getInstance()->removeAllObservers(this);

    Layer::onExit();
}

bool ChessboardController::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void ChessboardController::onTouchMoved(Touch* touch, Event* event)
{
    //    CCTouchDelegate
}

void ChessboardController::onTouchEnded(Touch *pTouch, Event *pEvent){
    logPoint(pTouch->getStartLocation());
    tryMove(RealToLogic(pTouch->getStartLocation()), RealToLogic(pTouch->getLocation()));
}

void ChessboardController::tryMove(const Vec2& src, const Vec2& dest){
    if (dest.equals(src))
        return;
    CCPoint newDest = (dest - src) / (dest - src).getLength() + src;
    Move move(chessboard->getCurrentMove().currentRound,src, newDest);
    if(chessboard->checkMessage(BEGIN_MOVE_MSG) && chessboard->checkMove(move)){
        chessboard->alterMove(move);
    }
    
}

void ChessboardController::tryEat(Ref* o){
    
    Move move(chessboard->getCurrentMove());
    if(chessboard->checkMessage(BEGIN_EAT_MSG)){
        if (chessboard->checkEat(move)){
            chessboard->alterEat(move);
        }else{
            chessboard->alterNextRound();
        }
    }
}

void ChessboardController::tryWin(Ref* o){
    if (chessboard->checkMessage(WIN_MSG)) {
        if (chessboard->checkWin(chessboard->getCurrentMove())){
            chessboard->alterWin();
            this->addChild(RotFlowerParticle::create());
        }else{
            chessboard->alterNextRound();
        }
    }
}

void ChessboardController::tryRegret(Ref *o){
    if (chessboard->checkMessage(REGRET_MSG)){
        chessboard->alterRegret();
        
        __String* frame_name = ( chessboard->getCurrentMove().currentRound == WHITE ) ? __String::create("black.png") : __String::create("white.png");
        
        for (Vec2 p : chessboard->getCurrentMove().eatenPoints) {
            SpriteFrameCache* cache = SpriteFrameCache::getInstance();
            Sprite* piece = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), p);
            this->addChild(piece);
        }
    }
}
