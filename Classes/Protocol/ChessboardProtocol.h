//
//  ChessboardProtocol.h
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#ifndef Four_ChessboardProtocol_h
#define Four_ChessboardProtocol_h

#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    ZERO,
    BLACK,
    WHITE,
} PIECE;

const int WIDTH = 4;
const int HEIGHT = 4;
const int PIECE_NUM = 4;

const int PIECE_WIDTH = 128;
const int PIECE_HEIGHT = 128;

const int X_OFFSET = 128;
const int Y_OFFSET = 288;

struct Move {
    PIECE currentRound;
    Vec2 src;
    Vec2 dest;
    std::vector<cocos2d::Vec2> eatenPoints;
    Move(PIECE _p):currentRound(_p){}
    Move(PIECE _p,const Vec2& _src, const Vec2& _dest):currentRound(_p),src(_src),dest(_dest){}
    Move(const Vec2& _src, const Vec2& _dest):src(_src),dest(_dest){}
    Move(const Move& _move):currentRound(_move.currentRound),src(_move.src),dest(_move.dest),eatenPoints(_move.eatenPoints){}
    void operator=(const Move& _move);
};

typedef std::vector< std::vector<PIECE> > ChessboardData;

void Pieces2Data(PIECE _pieces[][WIDTH], ChessboardData& data);

Vec2 LogicToReal(const cocos2d::Vec2& p);

Vec2 RealToLogic(const cocos2d::Vec2& p);

void logPoint(const cocos2d::Vec2& p);


#endif
