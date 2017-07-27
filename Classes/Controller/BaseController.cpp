//
//  BaseController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "BaseController.h"

bool BaseController::init(){
    if (!Layer::init()) {
        return false;
    }
    
    // load res
//    SpriteBatchNode* batch = SpriteBatchNode::create("AllSprites.png");
//    this->addChild(batch);
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("AllSprites.plist");
    
    // add background
    Sprite* background = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("background.png"));
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(0, 0));
    this->addChild(background);
    
    return true;
}
