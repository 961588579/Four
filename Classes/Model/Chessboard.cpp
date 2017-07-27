//
//  Chessboard.cpp
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#include "Chessboard.h"
#include "Message.h"
#include "ChessboardChecker.h"

#include <algorithm>

Chessboard::~Chessboard(){
//    cocos2d::__NotificationCenter::getInstance()->removeAllObservers(this);
}

bool Chessboard::init(){
    
    // 状态机实现
    Model::addTransition("start", BEGIN_MOVE_MSG, "moving")
        ->addTransition("start", REGRET_MSG, "back_moving")
    
        ->addTransition("start", AI_REGRET_MSG, "ai_back_moving")
        ->addTransition("ai_back_moving", AI_END_MOVE_MSG, "start")
    
        ->addTransition("back_moving", END_MOVE_MSG, "start")
        ->addTransition("moving", END_MOVE_MSG, "judge_eat")
        ->addTransition("judge_eat", NEXT_ROUND_MSG, "start")
        ->addTransition("judge_eat", BEGIN_EAT_MSG, "eating")
        ->addTransition("eating", END_EAT_MSG, "judge_win")
        ->addTransition("judge_win", NEXT_ROUND_MSG, "start")
        ->addTransition("judge_win", WIN_MSG, "win");
    
    PIECE _pieces[][WIDTH] = {
        { BLACK, BLACK, BLACK, BLACK },
        { ZERO, ZERO, ZERO, ZERO },
        { ZERO, ZERO, ZERO, ZERO },
        { WHITE, WHITE, WHITE, WHITE }
    };
   
    Pieces2Data(_pieces, pieces);
    
    using namespace cocos2d;
    
    // Add Listeners
    
    return true;
}

bool Chessboard::checkWin(const Move &move){
    return ::checkWin(pieces, move);
}

// 检查能否让某一方获胜,并且分发获胜事件
void Chessboard::alterWin(){
    this->onMessage(WIN_MSG);
}

bool Chessboard::checkEat(Move& move){
    return ::checkEat(pieces, move);
}

// 检测能否吃掉一个棋子
void Chessboard::alterEat(const Move& move){
    currentMove.eatenPoints = move.eatenPoints;
    std::vector<cocos2d::Vec2>& eatenPoints = currentMove.eatenPoints;
    

    for (auto point : eatenPoints) {
        this->setPiece(point, ZERO);
    }
    
    
    this->onMessage(BEGIN_EAT_MSG);
    
}


bool Chessboard::checkMove(const Move &move){
    return ::checkMove(this->pieces, move);
}

// 检测这一步是否能走，并且修改当前Point的值
void Chessboard::alterMove(const Move& move){
    
    currentMove.src = move.src;
    currentMove.dest =  move.dest;
    currentMove.eatenPoints.clear();
    
    // 将currentPoint的值改为目标位置的值
    this->setPiece(currentMove.src, ZERO);
    this->setPiece(currentMove.dest, currentMove.currentRound);
    
    this->onMessage(BEGIN_MOVE_MSG);
}

void Chessboard::setPiece(const cocos2d::Vec2& p, PIECE type){
    pieces[p.y][p.x] = type;
}

PIECE Chessboard::getPiece(const cocos2d::Vec2& p){
    return pieces[p.y][p.x];
}

void Chessboard::setPieces(PIECE _pieces[][WIDTH]){
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (getPiece(Vec2(j, i)) != ZERO )
                currentMove.eatenPoints.push_back(Vec2(j, i));
        }
    }
    cocos2d::__NotificationCenter::getInstance()->postNotification(BEGIN_EAT_MSG);
    pieces.clear();
    Pieces2Data(_pieces, pieces);
    return ;
}

void Chessboard::setPieces(const ChessboardData& data ){
    currentMove.eatenPoints.clear();
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (getPiece(Vec2(j, i)) != ZERO )
                currentMove.eatenPoints.push_back(Vec2(j, i));
        }
    }
    cocos2d::__NotificationCenter::getInstance()->postNotification(BEGIN_EAT_MSG);
    pieces.clear();
    pieces = data;
    return;
}

void Chessboard::alterNextRound(){
    Move move(currentMove);
    moves.push(move);
    currentMove.currentRound = oppositePiece(currentMove.currentRound);
    currentMove.src = Vec2(-1, -1);
    currentMove.dest = Vec2(-1, -1);
    currentMove.eatenPoints.clear();

    this->onMessage(NEXT_ROUND_MSG, this);
}


void Chessboard::alterRegret(){
    if (moves.empty())
        return;
    currentMove = moves.top();
    moves.pop();
    for (Vec2 p : currentMove.eatenPoints) {
        setPiece(p, oppositePiece(currentMove.currentRound));
    }
    setPiece(currentMove.dest, ZERO);
    setPiece(currentMove.src, currentMove.currentRound);
    this->onMessage(REGRET_MSG);
}

void Chessboard::alterAIRegret(){
    if (moves.empty())
        return;
    currentMove = moves.top();
    moves.pop();
    for (Vec2 p : currentMove.eatenPoints) {
        setPiece(p, oppositePiece(currentMove.currentRound));
    }
    setPiece(currentMove.dest, ZERO);
    setPiece(currentMove.src, currentMove.currentRound);
    this->onMessage(AI_REGRET_MSG);
}

void Chessboard::alterLose(){
    this->onMessage(LOSE_MSG);
}


