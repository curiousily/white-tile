//
//  SplashScene.h
//  whitetile
//
//  Created by Venelin Valkov on 5/1/14.
//
//

#ifndef __whitetile__SplashScene__
#define __whitetile__SplashScene__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Converter.h"
#include "MainMenuScene.h"

USING_NS_CC;

class Splash : public Layer, public AssetManager
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
        return "Splash";
    }

CREATE_FUNC(Splash)
};

#endif /* defined(__whitetile__SplashScene__) */
