//
//  GameScene.cpp
//  HitBubble
//
//  Created by DLL on 14/12/10.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

USING_NS_CC;

static float __bubbleNumberPerSecond;
static float __lastBubbleSecond;
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    scene = TransitionCrossFade::create(0.5, scene);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    mIsGameRunning = true;
    __bubbleNumberPerSecond = 2;
    mScore = 0;
    mMiss = 0;
    
    mBubbles = __Array::create();
    mBubbles->retain();
    
    Sprite *sprBg = Sprite::create("background.png");
    sprBg->setAnchorPoint(Vec2(0, 0));
    sprBg->setPosition(0, 0);
    this->addChild(sprBg);
    mWidth = this->getContentSize().width;
    mHeight = this->getContentSize().height;
    
    return true;
}

void GameScene::randomPlaceBubble(Bubble *bubble)
{
    Size size = bubble->getContentSize();
    bubble->setPosition(rand() % (int)(mWidth - size.width) + size.width / 2, -size.height);
    this->addChild(bubble);
    bubble->move();
    bubble->setDelegate(this);
    mBubbles->addObject(bubble);
}

GameScene::~GameScene()
{
    mBubbles->release();
}

void GameScene::update(float dt)
{
    Layer::update(dt);
    if (mIsGameRunning) {
        mTotalTime += dt;
//        Bubble::increaseSpeed((int)mTotalTime);
//        __bubbleNumberPerSecond += dt / 120;
        if (mTotalTime - __lastBubbleSecond >= 1 / __bubbleNumberPerSecond || __lastBubbleSecond == 0) {
            __lastBubbleSecond = mTotalTime;
            Bubble *bubble = Bubble::create();
            this->randomPlaceBubble(bubble);
        }
        for (int i = 0; i < mBubbles->count(); i++) {
            Bubble *bubble = (Bubble *)mBubbles->getObjectAtIndex(i);
            if (!bubble->getIsAlive() || bubble->getPositionY() >= mHeight + bubble->getContentSize().height) {
                if (bubble->getIsAlive()) {
                    mMiss++;
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("miss_bubble.wav");
                    this->checkGameOver();
                }
                bubble->removeFromParent();
                mBubbles->removeObjectAtIndex(i);
            }
        }
    }
}

void GameScene::onEnter()
{
    Layer::onEnter();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm01.mp3", true);
}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    __lastBubbleSecond = 0;
    mTotalTime = 0;
    this->scheduleUpdate();
}

void GameScene::onBubbleExplode(Bubble *bubble)
{
    mScore++;
    int randomSound = rand() % 6;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("explode0%d.mp3", randomSound)->getCString());
}

void GameScene::checkGameOver()
{
    if (mMiss >= 3) {
        mIsGameRunning = false;
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("failed.wav");
        for (int i = 0; i < mBubbles->count(); i++) {
            Bubble *bubble = (Bubble *)mBubbles->getObjectAtIndex(i);
            bubble->stopMoving();
        }
        Layer *deadLayer = LayerColor::create(Color4B(0, 0, 0, 127), mWidth, mHeight);
        __String* text = __String::createWithFormat("游戏结束\n得分：%d", mScore);
        Label *label = Label::createWithSystemFont(text->getCString(), "Arial", 70);
        label->setTextColor(Color4B(255, 0, 0, 255));
        label->setPosition(mWidth / 2, mHeight / 2 - 500);
        deadLayer->addChild(label);
        
        MenuItem *exitItem = MenuItemFont::create("点击继续", [&](Ref* ref) {
            auto menuScene = MenuScene::createScene();
            Director::getInstance()->replaceScene(menuScene);
        });
        Menu *menu = Menu::createWithItem(exitItem);
        menu->setPosition(mWidth / 2, mHeight / 2);
        deadLayer->addChild(menu);
        deadLayer->setPosition(0, 0);
        this->addChild(deadLayer);
    }
}
