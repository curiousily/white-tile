//
//  ZenHUD.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__ZenHUD__
#define __whitetile__ZenHUD__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Formatter.h"
#include "Converter.h"

USING_NS_CC;

class ZenHUD : public cocos2d::Layer, public AssetManager
{
public:
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
    return "Game/HUD";
}

void addScore(int score);

void startTimer();
void stopTimer();


CREATE_FUNC(ZenHUD);

void updateTimer(float delta);

private:

Label* timerLabel;
int nextClockSound;

CC_SYNTHESIZE_READONLY(int, score, Score)
};

#endif /* defined(__whitetile__ZenHUD__) */
