//
//  GameScene.h
//  HitBubble
//
//  Created by DLL on 14/12/10.
//
//

#ifndef __HitBubble__GameScene__
#define __HitBubble__GameScene__

#include <cocos2d.h>
#include "Bubble.h"

class GameScene : public cocos2d::Layer, public BubbleDeleagte
{
private:
    cocos2d::__Array *mBubbles;
    double mTime;
    int mWidth;
    int mHeight;
    void randomPlaceBubble(Bubble *bubble);
    float mTotalTime;
    bool mIsGameRunning;
    int mScore;
    int mMiss;
    void checkGameOver();
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    
    virtual ~GameScene();
    
    virtual void update(float dt);
    
    virtual void onBubbleExplode(Bubble *bubble);
};

#endif /* defined(__HitBubble__GameScene__) */
