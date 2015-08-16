//
//  SplashScene.cpp
//  whitetile
//
//  Created by Venelin Valkov on 5/1/14.
//
//

#include "SplashScene.h"

Scene* Splash::createScene() {
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool Splash::init() {
    if(!Layer::init()) {
        return false;
    }
    
    addBackground(this);
    
    runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 4), CallFunc::create([=](){
        Director::getInstance()->replaceScene(TransitionProgressInOut::create(SCENE_TRANSITION_TIME, MainMenu::createScene()));
    }), NULL));
    
    return true;
}