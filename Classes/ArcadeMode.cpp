//
//  ArcadeMode.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "ArcadeMode.h"

ArcadeMode* ArcadeMode::create(TileBoard* board) {
    auto mode = new ArcadeMode(board);
    mode->init();
    return mode;
}

void ArcadeMode::init() {
    HUDLayer = ArcadeHUD::create();
    
    moveSpeed = ARCADE_MODE_INITIAL_MOVE_SPEED;
    nextRowToTouch = 1;
    
    startTimer();
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addCustomEventListener("ResumeGame", [=](EventCustom* e) {
        startTimer();
    });
    eventDispatcher->addCustomEventListener("PauseGame", [=](EventCustom* e) {
        stopTimer();
    });
    eventDispatcher->addCustomEventListener("GameWin", [=](EventCustom* e) {
        stopTimer();
    });
}

void ArcadeMode::saveScore() {
    saveHighScore(HUDLayer->getScore());
}

Layer* ArcadeMode::getHUD() {
    return HUDLayer;
}

void ArcadeMode::onTilesTouch(cocos2d::EventCustom *e, std::vector<GameTile *> tiles) {
    bool touchOnPrevRow = false;
    for (auto tile: tiles) {
        auto tileType = tile->getType();
        auto tileRow = tile->getRow();
        if(tileRow != nextRowToTouch && tileRow != nextRowToTouch - 1) {
            e->stopPropagation();
            EventCustom event("GameWin");
            auto eventDispatcher = Director::getInstance()->getEventDispatcher();
            eventDispatcher->dispatchEvent(&event);
            stopTimer();
            board->stopAllActions();
            return;
        }
        if(tileRow == nextRowToTouch - 1) {
            touchOnPrevRow = true;
        }

        tile->onTouched();
        if(tileType == TileType::BLACK) {
            HUDLayer->addScore(BLACK_TILE_SCORE);
        } else if(tileType == TileType::BLUE) {
            HUDLayer->addScore(BLUE_TILE_SCORE);
        } else if(tileType == TileType::PINK) {
            HUDLayer->addScore(PINK_TILE_SCORE);
        }
    }
    if(!touchOnPrevRow) {
        nextRowToTouch++;
    }
}

void ArcadeMode::startTimer() {
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ArcadeMode::updateTimer, this), this, moveSpeed, kRepeatForever, TIMER_INITIAL_DELAY * 2, false, "updateTimer");
}

void ArcadeMode::stopTimer() {
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void ArcadeMode::resumeTimer() {
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ArcadeMode::updateTimer, this), this, moveSpeed, kRepeatForever, 0, false, "updateTimer");
}

void ArcadeMode::updateTimer(float delta) {
    if(board->getLowestRow() > nextRowToTouch) {
        EventCustom event("GameWin");
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->dispatchEvent(&event);
        stopTimer();
        board->stopAllActions();
        return;
    }
    board->moveRows(1, moveSpeed);
    board->addRow();
    moveSpeed = fmax(ARCADE_MODE_MINIMUM_SPEED, moveSpeed - ARCADE_MODE_SPEED_UP_FACTOR);
    stopTimer();
    resumeTimer();
}