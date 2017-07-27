//
//  AudioManager.cpp
//  Four
//
//  Created by 王选易 on 14-5-6.
//
//

#include "AudioManager.h"
#include "Message.h"

AudioManager::~AudioManager(){
    CC_SAFE_RELEASE(msg2audio);
}

bool AudioManager::init(){
    using namespace cocos2d;
    
    msg2audio = __Dictionary::create();
    CC_SAFE_RETAIN(msg2audio);
    FileUtils::getInstance()->addSearchPath("audio/");
    
    msg2audio->setObject(StringMake("move.WAV"), BEGIN_MOVE_MSG);
    msg2audio->setObject(StringMake("eat.WAV"), BEGIN_EAT_MSG);
    msg2audio->setObject(StringMake("next_round.WAV"), NEXT_ROUND_MSG);
    msg2audio->setObject(StringMake("click.WAV"), CLICK_MSG);
//    msg2audio->setObject(CCStringMake("create.WAV"), CREATE_MSG);
    
    DictElement* e = nullptr;
    CCDICT_FOREACH(msg2audio, e){
        __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(AudioManager::play), e->getStrKey(), e->getObject());
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(((CCString *)e->getObject())->getCString());
    }
    
    return true;
}

void AudioManager::play(Ref *str){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(((__String *)str)->getCString());
}

void AudioManager::pause(){
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void AudioManager::resume(){
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}
