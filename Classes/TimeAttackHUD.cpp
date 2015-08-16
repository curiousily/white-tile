//
//  TimeAttackHUD.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "TimeAttackHUD.h"

bool TimeAttackHUD::init() {
    std::string name = "TimeAttack";
    auto backgroundSprite = sprite(Formatter::toString("%sBackground", name.c_str()));
    addChild(backgroundSprite);
    setContentSize(backgroundSprite->getContentSize());
    backgroundSprite->setPosition(getContentSize().width * getAnchorPoint().x,
                                  getContentSize().height * getAnchorPoint().y);
    auto labelPosition = Point(getContentSize().width * getAnchorPoint().x + 250,
                               getContentSize().height * getAnchorPoint().y + 10);
    
    timerLabel = label("0.000")->position(labelPosition)->color(SCORE_COLOR)->addTo(this);
    
    auto pauseNormalSprite = sprite(Formatter::toString("%sPauseButtonNormal", name.c_str()));
    auto pausePressedSprite = sprite(Formatter::toString("%sPauseButtonPressed", name.c_str()));
    
    auto pauseButton = MenuItemSprite::create(pauseNormalSprite, pausePressedSprite, [=](Ref* sender) {
        playSoundEffect("Click");
        stopTimer();
        EventCustom event("PauseGame");
        _eventDispatcher->dispatchEvent(&event);
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
    
    _eventDispatcher->addCustomEventListener("GameWin", [=](EventCustom* e) {
        pauseButton->setEnabled(false);
        stopTimer();
    });
    
    _eventDispatcher->addCustomEventListener("GameLose", [=] (EventCustom* e){
        stopTimer();
    });
    
    return true;
}

void TimeAttackHUD::startTimer() {
    schedule(schedule_selector(TimeAttackHUD::updateTimer), TIMER_UPDATE_INTERVAL, kRepeatForever, TIMER_INITIAL_DELAY);
}

void TimeAttackHUD::stopTimer() {
    unscheduleAllSelectors();
}

void TimeAttackHUD::updateTimer(float delta) {
    auto time = timerLabel->getString();
    float timeFloat = Converter::toFloat(time);
    timeFloat += delta;
    timerLabel->setString(Formatter::toString("%.3f", timeFloat));
}

float TimeAttackHUD::getScore() {
    return Converter::toFloat(timerLabel->getString());
}