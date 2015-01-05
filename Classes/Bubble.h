//
//  Bubble.h
//  HitBubble
//
//  Created by DLL on 14/12/10.
//
//

#ifndef __HitBubble__Bubble__
#define __HitBubble__Bubble__

#include "cocos2d.h"

class BubbleDeleagte;

class Bubble : public cocos2d::Sprite {
public:
    virtual bool init();
    virtual ~Bubble();
    virtual void move();
    virtual void explode();
    virtual void cleanup();
    virtual void stopMoving();
    CREATE_FUNC(Bubble);
    CC_SYNTHESIZE(bool, alive, IsAlive);
    virtual void setDelegate(BubbleDeleagte *delegate);
    static void increaseSpeed(int time);
private:
    cocos2d::ActionInterval *moveAction;
    cocos2d::ActionInterval *explodeAction;
    cocos2d::EventListenerTouchOneByOne *mTouchListener;
    BubbleDeleagte *mDelegate;
};

class BubbleDeleagte {
public:
    virtual void onBubbleExplode(Bubble *bubble) = 0;
};

#endif /* defined(__HitBubble__Bubble__) */
