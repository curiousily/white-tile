//
//  ArcadeMode.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__ArcadeMode__
#define __whitetile__ArcadeMode__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Tile.h"
#include "PauseLayer.h"
#include "ArcadeHUD.h"
#include "ModeController.h"

USING_NS_CC;

class ArcadeMode : public ModeController {
    
public:
    
    ArcadeMode(TileBoard* board) : ModeController(board) {};
    
    static ArcadeMode* create(TileBoard* board);
    
    virtual Layer* getHUD() override;
    
    virtual void saveScore() override;
    
protected:
    
    void init();
    
    
    void startTimer();
    void stopTimer();
    void resumeTimer();
    
    virtual void onTilesTouch(EventCustom* e, std::vector<GameTile*>) override;
    
    void updateTimer(float delta);
    
    float moveSpeed;
    
    ArcadeHUD* HUDLayer;
    
    int nextRowToTouch;
    
};

#endif /* defined(__whitetile__ArcadeMode__) */
