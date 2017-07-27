//
//  AudioManager.h
//  Four
//
//  Created by 王选易 on 14-5-6.
//
//

#ifndef __Four__AudioManager__
#define __Four__AudioManager__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using CocosDenshion::SimpleAudioEngine;

class AudioManager : public Ref {
private:
    __Dictionary* msg2audio;
    
public:
    virtual ~AudioManager();
    bool init();
    CREATE_FUNC(AudioManager);
    
    void play(Ref* str);
    void pause();
    void resume();
    
};

#endif /* defined(__Four__AudioManager__) */
