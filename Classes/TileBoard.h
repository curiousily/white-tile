//
//  TileBoard.h
//  whitetile
//
//  Created by Venelin Valkov on 4/21/14.
//
//

#ifndef __whitetile__TileBoard__
#define __whitetile__TileBoard__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Tile.h"
#include "Random.h"
#include <vector>

class TileBoard : public cocos2d::Node, public AssetManager
{
public:
    
    bool init();
    
    const char* getResourceDirectory() override {
        return "Game";
    }

    void addRow();
    void moveRows(int rowCount, float duration);
    int getMaxRow();
    int getLowestRow();
    int getLowerNotUsedNonWhite(int row);
    void replaceTileOnVisibleRow(int row);
    void slideVisibleRow(int row);

    void onTileTouch(GameTile* tile);
    void simulateTouchOnTiles(GameTile* tile);

CREATE_FUNC(TileBoard)

private:

    int tileWidthPadding;
    int tileWidth;
    int tileHeight;
    int currentLowestRow;
    int currentMaxRow;

    std::set<int> usedRows;

    GameTile* getTile(int row, int column);
    int tileTagFor(int row, int column);
    void addTileAt(TileType type, int row, int column);

bool isRowNotUsed(int row);

void slideRow(int row, Direction direction);

int getTileColumnPosition(int column);
int getTileRowPosition(int row);

int chooseAvailableColumn(int usedColumn);

void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);

};

#endif /* defined(__whitetile__TileBoard__) */
