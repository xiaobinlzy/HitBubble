//
//  Bubble.cpp
//  HitBubble
//
//  Created by DLL on 14/12/10.
//
//

#include "Bubble.h"

USING_NS_CC;

static int __moveSpeed = 1000;
static int __moveSpeedRanRate = 500;
void Bubble::increaseSpeed(int time)
{
    __moveSpeed = 500 + time / 2;
    __moveSpeedRanRate = 200 + time * 2 / 5;
}

bool Bubble::init()
{
    if (!Sprite::init()) {
        return false;
    }
    mDelegate = NULL;
    
    this->setTexture("bubble_a.png");
    int speed = __moveSpeed + rand() % __moveSpeedRanRate - __moveSpeedRanRate / 2;
    
    MoveBy *moveBy = MoveBy::create(1, Vec2(0, speed));
    moveAction = RepeatForever::create(moveBy);
    moveAction->retain();
    
    explodeAction = Sequence::create(DelayTime::create(2), CallFunc::create([&]() {
        this->setIsAlive(false);
    }), NULL);
    explodeAction->retain();
    
    
    this->setIsAlive(true);
    mTouchListener = EventListenerTouchOneByOne::create();
    mTouchListener->retain();
    mTouchListener->setSwallowTouches(true);
    mTouchListener->onTouchBegan = [](Touch* touch, Event* event) {
        Bubble* target = static_cast<Bubble *>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode)) {
            Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(target);
            target->explode();
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mTouchListener, this);
    
    return true;
}

Bubble::~Bubble()
{

}

void Bubble::move()
{
    this->runAction(moveAction);
}

void Bubble::stopMoving()
{
    this->stopAction(moveAction);
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void Bubble::cleanup()
{
    CC_SAFE_RELEASE(moveAction);
    CC_SAFE_RELEASE(explodeAction);
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    mTouchListener->release();
    
    Sprite::cleanup();
}

void Bubble::explode()
{
    this->stopAction(moveAction);
    this->setTexture("bubble_d.png");
    this->runAction(explodeAction);
    if (mDelegate) {
        mDelegate->onBubbleExplode(this);
    }
    
}

void Bubble::setDelegate(BubbleDeleagte *delegate)
{
    mDelegate = delegate;
}