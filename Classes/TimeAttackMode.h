//
//  TimeAttackMode.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__TimeAttackMode__
#define __whitetile__TimeAttackMode__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Tile.h"
#include "PauseLayer.h"
#include "TimeAttackHUD.h"
#include "ModeController.h"

USING_NS_CC;

class TimeAttackMode : public ModeController {
    
public:
    
    TimeAttackMode(TileBoard* board) : ModeController(board) {};
    
    static TimeAttackMode* create(TileBoard* board);
    
    virtual Layer* getHUD() override;
    
    virtual void saveScore() override;
    
protected:
    
    void onTilesTouch(EventCustom* e, std::vector<GameTile*>) override;
    
    TimeAttackHUD* HUDLayer;
    
    int previousTileRow;
    
};

#endif /* defined(__whitetile__TimeAttackMode__) */
