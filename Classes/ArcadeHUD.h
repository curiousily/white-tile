//
//  ArcadeHUD.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__ArcadeHUD__
#define __whitetile__ArcadeHUD__


#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Formatter.h"
#include "TileBoard.h"

USING_NS_CC;

class ArcadeHUD : public cocos2d::Layer, public AssetManager
{
public:
    
    bool init();
    
    const char* getResourceDirectory() override {
        return "Game/HUD";
    }

    void addScore(int score);

    CREATE_FUNC(ArcadeHUD)

private:

    Label* scoreLabel;

    CC_SYNTHESIZE_READONLY(int, score, Score)


};

#endif /* defined(__whitetile__ArcadeHUD__) */
