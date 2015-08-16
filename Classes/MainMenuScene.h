//
//  MainMenuScene.h
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#ifndef __whitetile__MainMenuScene__
#define __whitetile__MainMenuScene__

#include "cocos2d.h"
#include "AssetManager.h"
#include "CountDownScene.h"
#include "NativeUtils.h"

class MainMenu : public cocos2d::LayerColor, public AssetManager
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
        return "MainMenu";
    }

CREATE_FUNC(MainMenu)

private:

void onPlayPress(Ref* sender);
};


#endif /* defined(__whitetile__MainMenuScene__) */
