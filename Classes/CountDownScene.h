//
//  CountDownScene.h
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#ifndef __whitetile__CountDownScene__
#define __whitetile__CountDownScene__


#include "cocos2d.h"
#include "AssetManager.h"
#include "Converter.h"
#include "HelloWorldScene.h"

class CountDown : public cocos2d::LayerColor, public AssetManager
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
    return "MainMenu";
}

CREATE_FUNC(CountDown)

Label* countDownLabel;

void startCountDown();

};


#endif /* defined(__whitetile__CountDownScene__) */
