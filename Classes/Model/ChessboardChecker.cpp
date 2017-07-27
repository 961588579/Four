//
//  ChessboardChecker.cpp
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#include "ChessboardChecker.h"

#include <vector>
#include <cmath>

using std::vector;

bool inbound(const Vec2& p, int width, int height){
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height;
}

bool inbound(const Vec2& p){
    return inbound(p, WIDTH, HEIGHT);
}

PIECE oppositePiece(PIECE p){
    return (p == BLACK ? WHITE : BLACK);
}

PIECE getPiece(const ChessboardData& pieces, const cocos2d::Vec2& p){
    return pieces[p.y][p.x];
}

bool checkWin( const ChessboardData& pieces, const Move& move ){
    PIECE enemyRound = oppositePiece(move.currentRound);
    int cnt = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (pieces[i][j] == enemyRound)
                cnt++;
        }
    }
    if (cnt < 2)
        return true;
    return false;
}

bool checkMove( const ChessboardData& pieces, const Move& move ){
    
    if ( inbound(move.src) && inbound(move.dest) && getPiece(pieces, move.src) == move.currentRound && getPiece(pieces, move.dest) == ZERO && (move.dest.x - (floor)(move.dest.x)) == 0)
        return true;
    return false;
}

bool checkEat( const ChessboardData& pieces, Move& move ){
    cocos2d::Vec2 currentPoint = move.dest;
    PIECE currentRound = move.currentRound;
    std::vector<cocos2d::Vec2>& eatenPoints = move.eatenPoints;
    
    cocos2d::Vec2 directions[4] = {Vec2(1, 0), Vec2(-1, 0), Vec2(0, 1), Vec2(0, -1)};
    for(auto direction : directions){
        Vec2 first = currentPoint + direction;
        if (inbound(first) && getPiece(pieces, first) == currentRound){
            Vec2 second = currentPoint + direction * 2;
            if (inbound(second)){
                Vec2 third = currentPoint + direction * 3;
                if (inbound(third)) {
                    if (getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO){
                        eatenPoints.push_back(second);
                    }
                }else{
                    third = currentPoint - direction;
                    if ((getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO)){
                        eatenPoints.push_back(second);
                    }else if (getPiece(pieces, third) == oppositePiece(currentRound) && getPiece(pieces, second) == ZERO){
                        eatenPoints.push_back(third);
                    }
                }
            }else{
                second = currentPoint - direction;
                Vec2 third = currentPoint - direction * 2;
                if (getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO){
                    eatenPoints.push_back(second);
                }
            }
        }
    }
        CCLOG("size : %lu", eatenPoints.size());

    
    if (eatenPoints.size() == 0)
        return false;
    logPoint(eatenPoints[0]);
    return true;
}
