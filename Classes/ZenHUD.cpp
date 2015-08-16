//
//  ZenHUD.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "ZenHUD.h"


bool ZenHUD::init() {
    std::string name = "Zen";
    auto backgroundSprite = sprite(Formatter::toString("%sBackground", name.c_str()));
    addChild(backgroundSprite);
    setContentSize(backgroundSprite->getContentSize());
    backgroundSprite->setPosition(getContentSize().width * getAnchorPoint().x,
                                  getContentSize().height * getAnchorPoint().y);
    auto labelPosition = Point(getContentSize().width * getAnchorPoint().x + 250,
                               getContentSize().height * getAnchorPoint().y + 10);
    
    timerLabel = label("30.000")->position(labelPosition)->color(SCORE_COLOR)->addTo(this);
    
    auto pauseNormalSprite = sprite(Formatter::toString("%sPauseButtonNormal", name.c_str()));
    auto pausePressedSprite = sprite(Formatter::toString("%sPauseButtonPressed", name.c_str()));
    
    auto pauseButton = MenuItemSprite::create(pauseNormalSprite, pausePressedSprite, [=](Ref* sender) {
        playSoundEffect("Click");
        EventCustom event("PauseGame");
        _eventDispatcher->dispatchEvent(&event);
        stopTimer();
    });
    pauseButton->setPosition(Point(labelPosition.x + 220, labelPosition.y));
    auto menu = Menu::create(pauseButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    startTimer();
    
    _eventDispatcher->addCustomEventListener("ResumeGame", [=](EventCustom* e) {
        startTimer();
    });
    
    _eventDispatcher->addCustomEventListener("PauseGame", [=](EventCustom* e) {
        stopTimer();
    });
    
    _eventDispatcher->addCustomEventListener("GameLose", [=] (EventCustom* e){
        stopTimer();
    });
    
    score = 0;
    nextClockSound = 5;
    return true;
}

void ZenHUD::startTimer() {
    schedule(schedule_selector(ZenHUD::updateTimer), TIMER_UPDATE_INTERVAL, kRepeatForever, TIMER_INITIAL_DELAY);
}

void ZenHUD::stopTimer() {
    unscheduleAllSelectors();
}

void ZenHUD::updateTimer(float delta) {
    auto time = timerLabel->getString();
    float timeFloat = Converter::toFloat(time);
    timeFloat -= delta;
    if(timeFloat < 0.0f) {
        stopTimer();
        timerLabel->setString("No Time");
        timerLabel->runAction(Blink::create(1.0f, 5));
        EventCustom event("GameWin");
        _eventDispatcher->dispatchEvent(&event);
    } else {
        if(timeFloat < nextClockSound) {
            playSoundEffect("ClockTick");
            nextClockSound--;
        }
        timerLabel->setString(Formatter::toString("%.3f", timeFloat));
    }

}

void ZenHUD::addScore(int score) {
    this->score += score;
}