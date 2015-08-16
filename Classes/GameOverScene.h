//
//  GameOverScene.h
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#ifndef __whitetile__GameOverScene__
#define __whitetile__GameOverScene__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Converter.h"
#include "MainMenuScene.h"
#include "CountDownScene.h"
#include "HighScoreManager.h"
#include "NativeUtils.h"
#include "PlayGameConstants.h"
#include "Constants.h"

class GameOver : public cocos2d::LayerColor, public AssetManager
{
public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(GameOver)
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
        return "GameOver";
    }

private:

void onNewHighScore(const char* highScoreKey, float score);
void showWinScreen();
Sprite* scoreBox;
GameMode gameMode;
};


#endif /* defined(__whitetile__GameOverScene__) */
