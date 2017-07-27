//
//  MenuController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "MenuController.h"
#include "ImageButton.h"
#include "StartScene.h"
#include "Message.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "C2DXShareSDK.h"

using namespace cn::sharesdk;

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            break;
        default:
            break;
    }
}

#endif

bool MenuController::init(){
    
    if (!Layer::init()) {
        return false;
    }


    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    Sprite* background = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("menubar.png"));
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(0, 0));
    this->addChild(background);
    
    Sprite* back = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("back.png"));
    ImageButton* backButton = ImageButton::create(back, this, menu_selector(MenuController::onBack));
    backButton->setPosition(Vec2(128, 48));
    
    Sprite* regret = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("regret.png"));
    ImageButton* regretButton = ImageButton::create(regret, this, menu_selector(MenuController::onRegret));
    regretButton->setPosition(Vec2(320, 48));
    
    Sprite* plus = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("plus.png"));
    ImageButton* plusButton = ImageButton::create(plus, this, menu_selector(MenuController::onShare));
    plusButton->setPosition(Vec2(512, 48));
    
    Menu* menu = Menu::create(backButton, regretButton, plusButton, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);
    
    return true;
}

void MenuController::onBack(Ref* o){
    __NotificationCenter::getInstance()->postNotification(CLICK_MSG);
    StartScene* ss = StartScene::create();
    TransitionSlideInL* slide = TransitionSlideInL::create(0.3f, ss);
    Director::getInstance()->replaceScene(slide);
}

void MenuController::onRegret(cocos2d::Ref *o){
    __NotificationCenter::getInstance()->postNotification(CLICK_MSG);
    __NotificationCenter::getInstance()->postNotification(CLICK_REGRET_MSG);
}

void MenuController::onShare(cocos2d::Ref *o){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    __NotificationCenter::getInstance()->postNotification(CLICK_MSG);
       CCDictionary *content = CCDictionary::create();
    content -> setObject(__String::create("这是一条测试内容"), "content");
    content -> setObject(__String::create("http://img0.bdstatic.com/img/image/308342ac65c10385343da168d569113b07ecb8088ef.jpg"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("测试描述"), "description");
    content -> setObject(__String::create("http://sharesdk.cn"), "url");
    content -> setObject(__String::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(__String::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(__String::create("ShareSDK"), "site");
    content -> setObject(__String::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(__String::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, Vec2Make(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
#endif
}

