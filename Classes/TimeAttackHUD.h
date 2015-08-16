//
//  TimeAttackHUD.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__TimeAttackHUD__
#define __whitetile__TimeAttackHUD__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Formatter.h"
#include "Converter.h"

USING_NS_CC;

class TimeAttackHUD : public cocos2d::Layer, public AssetManager
{
public:
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
    return "Game/HUD";
}

void startTimer();
void stopTimer();


CREATE_FUNC(TimeAttackHUD);

void updateTimer(float delta);

float getScore();

private:

Label* timerLabel;
};

#endif /* defined(__whitetile__TimeAttackHUD__) */
