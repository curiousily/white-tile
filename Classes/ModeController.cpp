//
//  ModeController.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "ModeController.h"

ModeController::ModeController(TileBoard* board) : board(board) {
    eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerCustom::create("NonWhiteTilesTouch", [=](EventCustom* e) {
        auto tiles = *static_cast<std::vector<GameTile*> *>(e->getUserData());
        onTilesTouch(e, tiles);
    });
    
    GameMode gameMode = static_cast<GameMode>(UserDefault::getInstance()->getIntegerForKey("mode", GameMode::ARCADE));
    
    eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    auto whiteTileTouchListener = EventListenerCustom::create("WhiteTileTouch", [=](EventCustom* e) {
        auto tile = static_cast<GameTile*>(e->getUserData());
        tile->onTouched();
        if(gameMode == GameMode::ARCADE) {
            EventCustom event("GameWin");
            eventDispatcher->dispatchEvent(&event);
        } else {
            EventCustom event("GameLose");
            eventDispatcher->dispatchEvent(&event);
        }

    });
    eventDispatcher->addEventListenerWithFixedPriority(whiteTileTouchListener, 1);
}

void ModeController::saveHighScore(float score) {
    auto db = UserDefault::getInstance();
    db->setFloatForKey(SCORE_KEY, score);
    db->flush();
}

void ModeController::replaceTile() {
    board->replaceTileOnVisibleRow(4);
    EventCustom event("ReplaceTile");
    eventDispatcher->dispatchEvent(&event);
}

void ModeController::slideRow() {
    board->slideVisibleRow(4);
    
    EventCustom event("SlideRow");
    eventDispatcher->dispatchEvent(&event);
}