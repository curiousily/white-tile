//
//  ZenMode.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "ZenMode.h"

ZenMode* ZenMode::create(TileBoard* board) {
    auto mode = new ZenMode(board);
    mode->HUDLayer = ZenHUD::create();
    mode->previousTileRow = 0;
    return mode;
}

Layer* ZenMode::getHUD() {
    return HUDLayer;
}

void ZenMode::onTilesTouch(cocos2d::EventCustom *e, std::vector<GameTile *> tiles){
    int usedRow = tiles[0]->getRow();
    for (auto tile: tiles) {
        auto tileType = tile->getType();
        int tileRow = tile->getRow();
        if(tileRow != usedRow || board->getLowerNotUsedNonWhite(tileRow) != -1) {
            e->stopPropagation();
            EventCustom event("GameLose");
            auto eventDispatcher = Director::getInstance()->getEventDispatcher();
            eventDispatcher->dispatchEvent(&event);
            return;
        }
        tile->onTouched();
        int moveRowCount = tileRow - previousTileRow;
        previousTileRow = tileRow;
        board->moveRows(moveRowCount, 0.3f);
        for (int i = 0; i < moveRowCount; i++) {
            board->addRow();
        }
        
        if (Random::hasLuck(TILE_CHANGE_CHANCE_PERCENT)) {
            replaceTile();
        } else if(Random::hasLuck(ROW_SLIDE_CHANCE_PERCENT)) {
            slideRow();
        }
        
        HUDLayer->addScore(BLACK_TILE_SCORE);
        if(tileType == TileType::BLUE) {
            HUDLayer->updateTimer(BLUE_TILE_TIME_REDUCE);
        } else if(tileType == TileType::PINK) {
            HUDLayer->updateTimer(PINK_TILE_TIME_REDUCE);
        }
    }
}

void ZenMode::saveScore() {
    saveHighScore(HUDLayer->getScore());
}