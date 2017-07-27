//
//  ChessboardProtocol.cpp
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#include "ChessboardProtocol.h"

void Pieces2Data(PIECE _pieces[][WIDTH], ChessboardData& data){
    for (int i = 0; i < HEIGHT; ++i) {
        data.push_back(std::vector<PIECE>(_pieces[i], _pieces[i] + WIDTH));
    }
}

Vec2 LogicToReal(const cocos2d::Vec2& p){
    return Vec2(X_OFFSET + p.x * PIECE_WIDTH, Y_OFFSET + p.y * PIECE_HEIGHT);
}

Vec2 RealToLogic(const cocos2d::Vec2& p){
    return Vec2(round((p.x - X_OFFSET) / PIECE_WIDTH ), round((p.y - Y_OFFSET) / PIECE_HEIGHT));
}

void Move::operator=(const Move &_move){
    this->currentRound = _move.currentRound;
    this->src = _move.src;
    this->dest = _move.dest;
    this->eatenPoints = _move.eatenPoints;
}

void logPoint(const cocos2d::Vec2& p){
    CCLOG("x:%f y:%f", p.x, p.y);
}
