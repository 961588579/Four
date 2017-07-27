//
//  TimeBoard.h
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#ifndef __Four__TimeBoard__
#define __Four__TimeBoard__

#include "cocos2d.h"

using namespace cocos2d;

class TimeBoard : public Label {
private:
    int leftSeconds;
    
public:
    bool init();
    CREATE_FUNC(TimeBoard);
    
    void onEnter();
    void onExit();
    
    void onTimeChanged(float dt);
    void onStop(Ref *ref);
};

#endif /* defined(__Four__TimeBoard__) */
