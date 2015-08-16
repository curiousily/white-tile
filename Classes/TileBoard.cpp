//
//  TileBoard.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/21/14.
//
//

#include "TileBoard.h"


bool TileBoard::init() {
    if( !Node::init())
    {
        return false;
    }
    
    auto visibleWidth = Director::getInstance()->getVisibleSize().width;
    tileWidth = sprite("WhiteTile")->getContentSize().width;
    tileHeight = sprite("WhiteTile")->getContentSize().height;
    
    tileWidthPadding = (visibleWidth - (4 * tileWidth)) / 5;

    currentLowestRow = 0;
    currentMaxRow = 0;
    for (int row = 1; row <= BOARD_ROWS; row++) {
        addRow();
    }
    addRow();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TileBoard::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void TileBoard::addTileAt(TileType type, int row, int column) {
    auto tile = GameTile::create(type, Point(getTileColumnPosition(column), getTileRowPosition(row)), row + 1, column + 1);
    tile->setTag(tileTagFor(row, column));
    addChild(tile);
}

int TileBoard::getTileColumnPosition(int column) {
    return tileWidth / 2 + ((column + 1) * tileWidthPadding) + column * tileWidth;
}

int TileBoard::getTileRowPosition(int row) {
    return tileHeight / 2 + row * tileHeight + (row * TILE_HEIGHT_PADDING);
}

GameTile* TileBoard::getTile(int row, int column) {
    return (GameTile*) getChildByTag(tileTagFor(row, column));
}

int TileBoard::tileTagFor(int row, int column) {
    return row * BOARD_COLUMNS + column;
}

void TileBoard::slideRow(int row, Direction direction) {
    row--;
    auto tileToDelete = getTile(row, 3);
    int newTileColumn = -1;
    int tileOffset = 1;
    int moveByX = tileWidthPadding + tileWidth;
    if(direction == Direction::LEFT) {
        newTileColumn = 4;
        moveByX = -moveByX;
        tileOffset = -1;
        tileToDelete = getTile(row, 0);
    }
    GameTile* newTile = GameTile::create(TileType::WHITE, Point(getTileColumnPosition(newTileColumn), getTileRowPosition(row)), row + 1, newTileColumn + tileOffset + 1);
    addChild(newTile);
    
    for(int column = 0; column < BOARD_COLUMNS; column++) {
        auto currentTile = getTile(row, column);
        currentTile->runAction(Sequence::create(MoveBy::create(0.5f, Point(moveByX, 0)), CallFunc::create([=](){
            currentTile->setColumn(column + tileOffset + 1);
            currentTile->setTag(tileTagFor(row, column + tileOffset));
        }), NULL) );
        currentTile->move();
    }


    newTile->runAction(Sequence::create(MoveBy::create(0.5f, Point(moveByX, 0)), CallFunc::create([=]() {
        newTile->setTag(tileTagFor(row, newTileColumn + tileOffset));
        tileToDelete->removeFromParent();
    }), NULL));
    newTile->move();
}

void TileBoard::addRow() {
    int blackTileColumn = Random::between(0, BOARD_COLUMNS);
    bool shouldAddPink = Random::hasLuck(ADD_PINK_CHANCE_PERCENT);
    
    int pinkTileColumn = -1;
    if(shouldAddPink) {
        pinkTileColumn = chooseAvailableColumn(blackTileColumn);
    }
    
    bool shouldAddBlue = Random::hasLuck(ADD_BLUE_CHANCE_PERCENT) && !shouldAddPink;
    
    int blueTileColumn = -1;
    if (shouldAddBlue) {
        blueTileColumn = chooseAvailableColumn(blackTileColumn);
    }
    for (int column = 0; column < BOARD_COLUMNS; column++) {
        auto type = blackTileColumn == column ? TileType::BLACK : TileType::WHITE;
        if(column == blueTileColumn) {
            type = TileType::BLUE;
        } else if(column == pinkTileColumn) {
            type = TileType::PINK;
        }
        addTileAt(type, currentMaxRow, column);
    }
    currentMaxRow += 1;
}

void TileBoard::moveRows(int rowCount, float duration) {
    if(rowCount < 1) {
        return;
    }
    runAction(Sequence::create(MoveBy::create(duration, Point(0, rowCount * (-(tileHeight + TILE_HEIGHT_PADDING)))),CallFunc::create([=]() {
        currentLowestRow += rowCount;
    }), NULL) );
}

int TileBoard::getMaxRow() {
    return currentMaxRow;
}

int TileBoard::getLowestRow() {
    return currentLowestRow + 1;
}

int TileBoard::getLowerNotUsedNonWhite(int row) {
    for(int nextRow = row - 1; nextRow >= currentLowestRow; nextRow--) {
        for (int column = 0; column < BOARD_COLUMNS; column++) {
            auto tile = getTile(nextRow, column);
            if(tile->getType() != TileType::WHITE && isRowNotUsed(nextRow)) {
                return nextRow + 1;
            }
        }
    }
    return -1;
}

void TileBoard::replaceTileOnVisibleRow(int row) {
    std::vector<GameTile*> availableTiles;
    for (int column = 0; column < BOARD_COLUMNS; column++) {
        auto aTile = getTile(currentLowestRow + row, column);
        if(aTile->getType() != TileType::WHITE) {
            availableTiles.push_back(aTile);
        }
    }
    if(!availableTiles.empty()) {
        Random::choose(availableTiles)->replace();
    }
}

void TileBoard::slideVisibleRow(int row) {
    slideRow(row + currentLowestRow, Random::hasLuck(50) ? Direction::LEFT : Direction::RIGHT);
}

int TileBoard::chooseAvailableColumn(int usedColumn) {
    std::vector<int> availableColumns;
    for(int column = 0; column < BOARD_COLUMNS; column++) {
        if (column != usedColumn) {
            availableColumns.push_back(column);
        }
    }
    return Random::choose(availableColumns);
}

void TileBoard::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event) {
    std::vector<GameTile*> touchedTiles;
    for ( auto &touch: touches )
    {
        auto location = touch->getLocation();
        for(int row = currentLowestRow; row < currentMaxRow ; row++) {
            for (int column = 0; column < BOARD_COLUMNS; column++) {
                auto tile = getTile(row, column);
                if(tile->isOnTile(location)) {
                    if(tile->getType() == TileType::WHITE) {
                        EventCustom event("WhiteTileTouch");
                        event.setUserData(tile);
                        _eventDispatcher->dispatchEvent(&event);
                        return;
                    } else {
                        usedRows.insert(tile->getRow() - 1);
                        touchedTiles.push_back(tile);
                    }
                }
            }
        }
    }
    if(touchedTiles.size() > 0) {
        EventCustom e("NonWhiteTilesTouch");
        e.setUserData(&touchedTiles);
        _eventDispatcher->dispatchEvent(&e);
    }
}

void TileBoard::simulateTouchOnTiles(GameTile* tile) {
    for(int row = currentLowestRow; row < currentMaxRow ; row++) {
        for (int column = 0; column < BOARD_COLUMNS; column++) {
            auto aTile = getTile(row, column);
            if(aTile->getType() != TileType::WHITE && tile != aTile) {
                aTile->onTouched();
            }
        }
    }
}

bool TileBoard::isRowNotUsed(int row) {
    return usedRows.find(row) == usedRows.end();
}