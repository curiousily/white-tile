//
//  Tile.h
//  whitetile
//
//  Created by Venelin Valkov on 4/11/14.
//
//

#ifndef __whitetile__Tile__
#define __whitetile__Tile__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "AnimatedNode.h"
#include "Formatter.h"

enum class TileType {
    BLACK,
    WHITE,
    PINK,
    BLUE
};

class GameTile : public cocos2d::Node, public AssetManager
{
public:
    
    static GameTile* create(TileType tileType, const Point& position, int row, int column);
    
    void init(TileType tileType, const Point& position, int row, int column);
    
    const char* getResourceDirectory() override {
        return "Game";
    }

    bool isOnTile(Point point);

    void onTouched();

    void replace();

    void move();

private:
    Sprite* tileSprite;

    static const int TOUCH_ANIMATION_NODE_TAG = 1;

CC_SYNTHESIZE_READONLY(TileType, type, Type)
CC_SYNTHESIZE(int, row, Row)
CC_SYNTHESIZE(int, column, Column)
CC_SYNTHESIZE_READONLY(std::string, name, Name)

    void setNameFromType();
};

#endif /* defined(__whitetile__Tile__) */
