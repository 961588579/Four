//
//  PieceView.h
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#ifndef __Four__PieceView__
#define __Four__PieceView__

#include "cocos2d.h"
#include "Model.h"
#include "ChessboardProtocol.h"

using namespace cocos2d;

class PieceView : public Sprite{
    CC_SYNTHESIZE(const Move*, currentMove, CurrentMove);
    CC_SYNTHESIZE(Model*, model, Model);
    CC_SYNTHESIZE(ActionInterval*, dropAction, DropAction);
    
private:
    bool containsTouchLocation(Touch* touch);
    
public:
    PieceView(){}
    virtual ~PieceView();
    virtual bool init();
    CREATE_FUNC(PieceView);
    static PieceView* create(const Move* _currentMove, Model* _model, SpriteFrame* frame, const Vec2& _logic_position);
    
    void onEnter();
    void onExit();
    
    // listener
    void onBeginMove(Ref* o);
    void onBeginEat(Ref* o);
    void onRegret(Ref* o);
    void onAIRegret(Ref* o);
};

#endif /* defined(__Four__PieceView__) */
