//
//  MenuScene.h
//  HitBubble
//
//  Created by DLL on 14/12/11.
//
//

#ifndef __HitBubble__MenuScene__
#define __HitBubble__MenuScene__

#include "cocos2d.h"
class MenuScene : public cocos2d::LayerColor {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuScene);
    virtual ~MenuScene();
    virtual void exitGame();
    virtual void playGame();
};

#endif /* defined(__HitBubble__MenuScene__) */
