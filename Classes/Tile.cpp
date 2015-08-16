//
//  Tile.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/11/14.
//
//

#include "Tile.h"

GameTile* GameTile::create(TileType tileType, const Point& position, int row, int column) {
    auto tile = new GameTile();
    if(tile) {
        tile->init(tileType, position, row, column);
        tile->autorelease();
    } else {
        CC_SAFE_DELETE(tile);
    }
    return tile;
}

void GameTile::init(TileType tileType, const Point& position, int row, int column) {
    Node::init();
    this->type = tileType;
    this->row = row;
    this->column = column;
    setNameFromType();
    tileSprite = sprite(Formatter::toString("%s", name.c_str()));
    setPosition(position);
    setContentSize(tileSprite->getContentSize());
    addChild(tileSprite);
}

bool GameTile::isOnTile(Point point) {
    Point locationInNode = tileSprite->convertToNodeSpace(point);
    Size s = tileSprite->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    return false;
}

void GameTile::onTouched() {
    tileSprite->setVisible(false);
    auto previousAnimation = getChildByTag(TOUCH_ANIMATION_NODE_TAG);
    if(previousAnimation != nullptr) {
        return;
    }
    auto spritePosition = tileSprite->getPosition();
    auto animatedNode = AnimatedNode::create(Formatter::toString("%sTouch", name.c_str()));
    animatedNode->setTag(TOUCH_ANIMATION_NODE_TAG);
    addChild(animatedNode);
    animatedNode->setPosition(spritePosition);
    animatedNode->play([=](){
        animatedNode->removeFromParent();
        tileSprite->setVisible(true);
        EventCustom event("TileTouchAnimationDone");
        event.setUserData(this);
        _eventDispatcher->dispatchEvent(&event);
    }, 0.05f);
}

void GameTile::replace() {
    auto previousAnimation = getChildByTag(TOUCH_ANIMATION_NODE_TAG);
    if(previousAnimation != nullptr) {
        auto animationNode = (AnimatedNode*) previousAnimation;
        animationNode->stop();
        animationNode->removeFromParent();
    }
    tileSprite->setVisible(false);
    auto spritePosition = tileSprite->getPosition();
    auto animatedNode = AnimatedNode::create(Formatter::toString("%sToWhiteTile", name.c_str()));
    addChild(animatedNode);
    animatedNode->setPosition(spritePosition);
    type = TileType::WHITE;
    setNameFromType();
    animatedNode->play([=](){
        animatedNode->removeFromParent();
        tileSprite->removeFromParentAndCleanup(true);
        tileSprite = sprite("WhiteTile", spritePosition);
        addChild(tileSprite);
        tileSprite->setVisible(true);
    }, 0.1f);
}

void GameTile::move() {
    tileSprite->setVisible(false);
    auto spritePosition = tileSprite->getPosition();
    auto animatedNode = AnimatedNode::create(Formatter::toString("%sWobble", name.c_str()));
    addChild(animatedNode);
    animatedNode->setPosition(spritePosition);
    animatedNode->play([=](){
        animatedNode->removeFromParent();
        tileSprite->setVisible(true);
    }, 0.1f);
}

void GameTile::setNameFromType() {
    switch (type) {
        case TileType::PINK:
            name = "PinkTile";
            break;
        case TileType::BLUE:
            name = "BlueTile";
            break;
        case TileType::BLACK:
            name = "BlackTile";
            break;
        default:
            name = "WhiteTile";
            break;
    }
}