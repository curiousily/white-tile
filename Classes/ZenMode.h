//
//  ZenMode.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__ZenMode__
#define __whitetile__ZenMode__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Tile.h"
#include "PauseLayer.h"
#include "ZenHUD.h"
#include "ModeController.h"

USING_NS_CC;

class ZenMode : public ModeController {
    
public:
    
    ZenMode(TileBoard* board) : ModeController(board) {};
    
    static ZenMode* create(TileBoard* board);
    
    virtual Layer* getHUD() override;
    
    virtual void saveScore() override;
    
protected:
    
    virtual void onTilesTouch(EventCustom* e, std::vector<GameTile*>) override;
    
    ZenHUD* HUDLayer;
    int previousTileRow;
};

#endif /* defined(__whitetile__ZenMode__) */
