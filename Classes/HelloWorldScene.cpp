#include "HelloWorldScene.h"
#include "VisibleRect.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if(!LayerColor::initWithColor(GAME_BACKGROUND_COLOR))
    {
        return false;
    }
    
    nextChar = 'A';
    
    gameBoard = TileBoard::create();
    
    addChild(gameBoard);
    
    GameMode gameMode = static_cast<GameMode>(UserDefault::getInstance()->getIntegerForKey("mode", GameMode::ARCADE));

    switch (gameMode) {
        case GameMode::ARCADE:
            modeController = ArcadeMode::create(gameBoard);
            break;
            
        case GameMode::TIME_ATTACK:
            modeController = TimeAttackMode::create(gameBoard);
            break;
        default:
            modeController = ZenMode::create(gameBoard);
            break;
    }

    gameHUDLayer = modeController->getHUD();
    gameHUDLayer->setPosition(Point(VisibleRect::left().x, VisibleRect::top().y - gameHUDLayer->getContentSize().height));
    addChild(gameHUDLayer);
    auto listener = EventListenerCustom::create("NonWhiteTilesTouch", CC_CALLBACK_1(HelloWorld::onTileTouch, this));
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 2);
    
    _eventDispatcher->addCustomEventListener("PauseGame", [=](EventCustom* e) {

        if(getChildByTag(10) == nullptr) {
            auto pauseLayer = PauseLayer::create();
            pauseLayer->setTag(10);
            addChild(pauseLayer);
        }
    });
    
    _eventDispatcher->addCustomEventListener("GameLose", [=] (EventCustom* e){
        onGameLose();
    });
    
    _eventDispatcher->addCustomEventListener("GameWin", [=](EventCustom* e) {
        onGameWin();
    });

    _eventDispatcher->addCustomEventListener("ReplaceTile", [=](EventCustom* e) {
        onTileReplace();
    });

    _eventDispatcher->addCustomEventListener("SlideRow", [=](EventCustom* e) {
        onSlideRow();
    });
    
    return true;
}
                                                
void HelloWorld::onTileTouch(cocos2d::EventCustom *event) {
    auto tiles = *static_cast<std::vector<GameTile*> *>(event->getUserData());
    gameBoard->simulateTouchOnTiles(tiles[0]);
    for(auto tile : tiles ) {
        auto tileType = tile->getType();
        std::string soundEffect = "TileTouch/sound";
        soundEffect += nextChar;
        switch (tileType) {
            case TileType::BLACK:
                playSoundEffect(soundEffect.c_str());
                if(nextChar + 1 > 'Z') {
                    nextChar = 'A';
                } else {
                    nextChar++;
                }
                break;
                
                
            case TileType::PINK:
                playSoundEffect("PinkTileTouch");
                break;
                
            case TileType::BLUE:
                playSoundEffect("BlueTileTouch");
                break;
                
                
            default:
                break;
        }
    }
}

void HelloWorld::onGameWin() {
    CCLOG("Game Win");
    modeController->saveScore();
    UserDefault::getInstance()->setBoolForKey(IS_WIN_KEY, true);
    delayAndShowGameOver();
}

void HelloWorld::onGameLose() {
    CCLOG("Game Lose");
    playSoundEffect("Error");
    UserDefault::getInstance()->setBoolForKey(IS_WIN_KEY, false);
    delayAndShowGameOver();
}

void HelloWorld::delayAndShowGameOver() {
    _eventDispatcher->removeAllEventListeners();
    runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 2), CallFunc::create([=](){
        Director::getInstance()->replaceScene(TransitionShrinkGrow::create(SCENE_TRANSITION_TIME, GameOver::createScene()));
    }), NULL));
}

void HelloWorld::onTileReplace() {
    playSoundEffect("ReplaceTile");
}

void HelloWorld::onSlideRow() {
    playSoundEffect("SlideRow");
}
