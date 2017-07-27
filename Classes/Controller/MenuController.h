//
//  MenuController.h
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#ifndef __Four__MenuController__
#define __Four__MenuController__

#include "cocos2d.h"

using namespace cocos2d;

class MenuController : public Layer{
    
public:
    bool init();
    CREATE_FUNC(MenuController);
    
    void onBack(Ref* o);
    void onRegret(Ref* o);
    void onShare(Ref* o);
};


#endif /* defined(__Four__MenuController__) */

