//
//  CountDownScene.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#include "CountDownScene.h"

Scene* CountDown::createScene() {
    auto scene = Scene::create();
    auto layer = CountDown::create();
    scene->addChild(layer);
    return scene;
}

bool CountDown::init() {
    if(!LayerColor::initWithColor(MENU_BACKGROUND_COLOR)) {
        return false;
    }
    
    countDownLabel = label("3")->position(VisibleRect::center())->size(500)->addTo(this);
    
    runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([&](){
        startCountDown();
    }), NULL));
    
    return true;
}

void CountDown::startCountDown() {

    SoundManager::sharedSoundManager()->playSoundEffect("ClockTick");
    countDownLabel->runAction(Sequence::create(EaseBackInOut::create(ScaleTo::create(0.4, 4.0f)),
                                               EaseBackOut::create(ScaleTo::create(0.4, 1.0f)),
                                               CallFunc::create([&]() {

        auto currentString = countDownLabel->getString();
        int currentNumber = Converter::toInt(currentString);
        currentNumber--;
        if(currentNumber > 0) {
            countDownLabel->setString(Converter::toString(currentNumber));
            startCountDown();
        } else {
            countDownLabel->setString("GO");
            SoundManager::sharedSoundManager()->playSoundEffect("Start");
            Director::getInstance()->replaceScene(TransitionProgressInOut::create(SCENE_TRANSITION_TIME,HelloWorld::createScene()));
        }
    }), NULL));
}