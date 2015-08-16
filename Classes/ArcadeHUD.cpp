//
//  ArcadeHUD.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "ArcadeHUD.h"


bool ArcadeHUD::init() {
    
    if(!Layer::init()) {
        return false;
    }    
    
    std::string name = "Arcade";
    auto backgroundSprite = sprite(Formatter::toString("%sBackground", name.c_str()));
    addChild(backgroundSprite);
    setContentSize(backgroundSprite->getContentSize());
    backgroundSprite->setPosition(getContentSize().width * getAnchorPoint().x,
                                  getContentSize().height * getAnchorPoint().y);
    auto labelPosition = Point(getContentSize().width * getAnchorPoint().x + 250,
                               getContentSize().height * getAnchorPoint().y + 10);

    scoreLabel = label("0")->position(labelPosition)->color(SCORE_COLOR)->addTo(this);
    score = 0;
    
    auto pauseNormalSprite = sprite(Formatter::toString("%sPauseButtonNormal", name.c_str()));
    auto pausePressedSprite = sprite(Formatter::toString("%sPauseButtonPressed", name.c_str()));
    
    auto pauseButton = MenuItemSprite::create(pauseNormalSprite, pausePressedSprite, [=](Ref* sender) {
        playSoundEffect("Click");
        EventCustom event("PauseGame");
        _eventDispatcher->dispatchEvent(&event);
    });
    pauseButton->setPosition(Point(labelPosition.x + 220, labelPosition.y));
    auto menu = Menu::create(pauseButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    return true;
}


void ArcadeHUD::addScore(int score) {
    this->score += score;
    scoreLabel->setString(Formatter::toString("%d", this->score));
}