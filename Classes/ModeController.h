//
//  ModeController.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__ModeController__
#define __whitetile__ModeController__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Formatter.h"
#include "TileBoard.h"

USING_NS_CC;

class ModeController {
    
public:
    
    ModeController(TileBoard* board);
    
    virtual Layer* getHUD() = 0;
    
    virtual void saveScore() = 0;
    
    virtual ~ModeController() {};
    
protected:
    
    virtual void onTilesTouch(EventCustom* e, std::vector<GameTile*>) = 0;
    void saveHighScore(float score);
    
    void replaceTile();
    void slideRow();
    
    TileBoard* board;
    EventDispatcher* eventDispatcher;
};

#endif /* defined(__whitetile__ModeController__) */
