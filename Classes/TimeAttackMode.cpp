//
//  TimeAttackMode.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "TimeAttackMode.h"

TimeAttackMode* TimeAttackMode::create(TileBoard* board) {
    auto mode = new TimeAttackMode(board);
    mode->HUDLayer = TimeAttackHUD::create();
    mode->previousTileRow = 0;
    return mode;
}

Layer* TimeAttackMode::getHUD() {
    return HUDLayer;
}

void TimeAttackMode::saveScore() {
    saveHighScore(HUDLayer->getScore());
}

void TimeAttackMode::onTilesTouch(cocos2d::EventCustom *e, std::vector<GameTile *> tiles) {
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
        
        if(tile->getRow() == TIME_ATTACK_ROWS_TO_RUN) {
            auto eventDispatcher = Director::getInstance()->getEventDispatcher();
            EventCustom event("GameWin");
            eventDispatcher->dispatchEvent(&event);
            return;
        }
        
        if (Random::hasLuck(TILE_CHANGE_CHANCE_PERCENT)) {
            replaceTile();
        } else if(Random::hasLuck(ROW_SLIDE_CHANCE_PERCENT)) {
            slideRow();
        }
        
        if(board->getMaxRow() != TIME_ATTACK_ROWS_TO_RUN) {
            for (int i = 0; i < moveRowCount; i++) {
                board->addRow();
            }
        }
        
        if(tileType == TileType::BLUE) {
            HUDLayer->updateTimer(-BLUE_TILE_TIME_REDUCE);
        } else if(tileType == TileType::PINK) {
            HUDLayer->updateTimer(-PINK_TILE_TIME_REDUCE);
        }
    }
}