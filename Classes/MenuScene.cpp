//
//  MenuScene.cpp
//  HitBubble
//
//  Created by DLL on 14/12/11.
//
//

#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

MenuScene::~MenuScene()
{
    
}

bool MenuScene::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) {
        return false;
    }

    MenuItemFont::setFontSize(100);
    MenuItem *item1 = MenuItemFont::create("开始游戏", [&](Ref *sender) {
        this->playGame();
    });
    MenuItem *item2 = MenuItemFont::create("退出", [&](Ref *sender) {
        this->exitGame();
    });
    Menu *menu = Menu::create(item1, item2, NULL);
    menu->alignItemsVerticallyWithPadding(200);
    menu->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    this->addChild(menu);

    return true;
}

Scene* MenuScene::createScene()
{
    Scene *scene = Scene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    scene = TransitionCrossFade::create(0.5, scene);
    return scene;
}

void MenuScene::exitGame()
{
    exit(0);
}

void MenuScene::playGame()
{
    Scene *gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
}