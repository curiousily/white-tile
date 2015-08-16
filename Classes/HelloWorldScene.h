#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Tile.h"
#include "TileBoard.h"
#include "GameOverScene.h"
#include "AnimatedNode.h"
#include "PauseLayer.h"
#include "ArcadeMode.h"
#include "TimeAttackMode.h"
#include "ZenMode.h"

class HelloWorld : public cocos2d::LayerColor, public AssetManager
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    const char* getResourceDirectory() override {
    return "Game";
}

    virtual ~HelloWorld() {
        CC_SAFE_DELETE(modeController);
    }

CREATE_FUNC(HelloWorld);

private:

TileBoard* gameBoard;
Layer* gameHUDLayer;

void onTileTouch(EventCustom* event);

void onGameWin();
void onGameLose();
void onTileReplace();
void onSlideRow();

void delayAndShowGameOver();

char nextChar;

ModeController* modeController;
};

#endif // __HELLOWORLD_SCENE_H__
