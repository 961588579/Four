//
//  ChessboardController.h
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#ifndef __Four__ChessboardController__
#define __Four__ChessboardController__

#include "ChessboardProtocol.h"
#include "BaseController.h"

#include "cocos2d.h"

using namespace cocos2d;

class Chessboard;

class ChessboardController : public BaseController  {
protected:
    Chessboard* chessboard;
    Label* modeLabel;
    
    void initPieceViews();
    
public:
    virtual bool init();
    virtual ~ChessboardController();
    
    CREATE_FUNC(ChessboardController);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    // try方法, 向Model请求进行操作
    virtual void tryMove(const Vec2& src, const Vec2& dest);
    virtual void tryEat(Ref* o);
    virtual void tryWin(Ref* o);
    virtual void tryRegret(Ref* o);
};



#endif /* defined(__Four__ChessboardController__) */
