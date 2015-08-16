//
//  MainMenuScene.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#include "MainMenuScene.h"

Scene* MainMenu::createScene() {
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init() {
    if(!LayerColor::initWithColor(MENU_BACKGROUND_COLOR)) {
        return false;
    }
    
    auto titleFinalPosition = Point(VisibleRect::top().x, 1920 - 202);
    auto titleSprite = sprite("Title", Point(titleFinalPosition.x, titleFinalPosition.y + 300));
    
    addChild(titleSprite);
    
    titleSprite->runAction(EaseSineOut::create(MoveTo::create(DEFAULT_ANIMATION_TIME, titleFinalPosition)));
    
    auto menuBackground = sprite("MenuBackground", Point(VisibleRect::center().x, 1920 - 966));
    menuBackground->setScale(1.0f, 0.1);
    menuBackground->runAction(ScaleTo::create(DEFAULT_ANIMATION_TIME, 1.0f));
    addChild(menuBackground);

    auto arcadeButtonFinalPosition = Point(335, 1288);
    
    auto arcadeButton = MenuItemSprite::create(sprite("ArcadeButtonNormal"), sprite("ArcadeButtonPressed"), [=] (Ref* sender) {
        auto userDefault = UserDefault::getInstance();
        userDefault->setIntegerForKey("mode", GameMode::ARCADE);
        onPlayPress(sender);
    });
    arcadeButton->setPosition(arcadeButtonFinalPosition.x, arcadeButtonFinalPosition.y + 2000);
    arcadeButton->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME), EaseBounceOut::create(MoveTo::create(DEFAULT_ANIMATION_TIME, arcadeButtonFinalPosition)), CallFunc::create([=](){
        arcadeButton->runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 4), RotateTo::create(DEFAULT_ANIMATION_TIME / 2, TILE_ROTATION_DEGREE), RotateTo::create(DEFAULT_ANIMATION_TIME, -TILE_ROTATION_DEGREE),RotateTo::create(DEFAULT_ANIMATION_TIME / 2, 0.0f),NULL)));
    }), NULL) );
    
    auto timeAttackButtonFinalPosition = Point(788, 1920 - 932);
    auto timeAttackButton = MenuItemSprite::create(sprite("TimeAttackButtonNormal"), sprite("TimeAttackButtonPressed"), [=] (Ref* sender) {
        auto userDefault = UserDefault::getInstance();
        userDefault->setIntegerForKey("mode", GameMode::TIME_ATTACK);
        onPlayPress(sender);
    });
    timeAttackButton->setPosition(timeAttackButtonFinalPosition.x, timeAttackButtonFinalPosition.y + 2000);
    
    timeAttackButton->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 2), EaseBounceOut::create(MoveTo::create(DEFAULT_ANIMATION_TIME, timeAttackButtonFinalPosition)), CallFunc::create([=](){
        timeAttackButton->runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 4), RotateTo::create(DEFAULT_ANIMATION_TIME / 2, TILE_ROTATION_DEGREE), RotateTo::create(DEFAULT_ANIMATION_TIME, -TILE_ROTATION_DEGREE),RotateTo::create(DEFAULT_ANIMATION_TIME / 2, 0.0f),NULL)));
    }), NULL) );

    auto zenButtonFinalPosition = Point(335, 1920 - 1251);
    auto zenButton = MenuItemSprite::create(sprite("ZenButtonNormal"), sprite("ZenButtonPressed"), [=] (Ref* sender) {
        auto userDefault = UserDefault::getInstance();
        userDefault->setIntegerForKey("mode", GameMode::ZEN);
        onPlayPress(sender);
    });
    zenButton->setPosition(zenButtonFinalPosition.x, zenButtonFinalPosition.y + 2000);
    zenButton->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 3), EaseBounceOut::create(MoveTo::create(DEFAULT_ANIMATION_TIME, zenButtonFinalPosition)), CallFunc::create([=](){
        zenButton->runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 4), RotateTo::create(DEFAULT_ANIMATION_TIME / 2, TILE_ROTATION_DEGREE), RotateTo::create(DEFAULT_ANIMATION_TIME, -TILE_ROTATION_DEGREE),RotateTo::create(DEFAULT_ANIMATION_TIME / 2, 0.0f),NULL)));
    }), NULL) );
    
    auto arcadeLabel = label("ARCADE")->size(MENU_FONT_SIZE)->position(Point(timeAttackButtonFinalPosition.x, arcadeButtonFinalPosition.y))->color(ARCADE_TEXT_COLOR)->addTo(this);
    arcadeLabel->setVisible(false);
    arcadeLabel->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 3),  Show::create(), NULL));
    
    auto timeAttackLabel = label("  TIME\nATTACK")->size(MENU_FONT_SIZE)->position(Point(arcadeButtonFinalPosition.x, timeAttackButtonFinalPosition.y))->color(TIME_ATTACK_TEXT_COLOR)->addTo(this);
    timeAttackLabel->setVisible(false);
    timeAttackLabel->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 4),  Show::create(), NULL));
    
    auto zenLabel = label("ZEN")->size(MENU_FONT_SIZE)->position(Point(timeAttackButtonFinalPosition.x, zenButtonFinalPosition.y))->color(ZEN_TEXT_COLOR)->addTo(this);
    zenLabel->setVisible(false);
    zenLabel->runAction(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 5),  Show::create(), NULL));
    
    auto soundManager = SoundManager::sharedSoundManager();
    
    auto soundButtonOn = MenuItemSprite::create(sprite("SoundButtonOn"), nullptr);
    auto soundButton = MenuItemToggle::createWithCallback([=](Ref* sender) {
        auto button = (MenuItemToggle*) sender;
        if(button->getSelectedItem() == soundButtonOn) {
            soundManager->unmuteSound();
        } else {
            soundManager->muteSound();
        }
        playSoundEffect("Click");
    }, soundButtonOn, MenuItemSprite::create(sprite("SoundButtonOff"), nullptr), NULL);
    
    if(soundManager->isSoundEnabled()) {
        soundButton->setSelectedIndex(0);
    } else {
        soundButton->setSelectedIndex(1);
    }
    
    soundButton->setPosition(Point(291, 1920 - 1710));
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    auto leaderBoardButton = MenuItemSprite::create(sprite("LeaderboardButtonNormal"), sprite("LeaderboardButtonPressed"), [=] (Ref* sender) {
        playSoundEffect("Click");
        NativeUtils::showLeaderboards();
    });
    leaderBoardButton->setPosition(Point(796, 1920 - 1710));
    
    auto menu = Menu::create(arcadeButton, timeAttackButton, zenButton, soundButton, leaderBoardButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
#else
    
    auto menu = Menu::create(arcadeButton, timeAttackButton, zenButton, soundButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
#endif
    
    
    runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 12), CallFunc::create([=] () {
        playSoundEffect("Giggle");
    }) , NULL)));
    
    return true;
}

void MainMenu::onPlayPress(Ref* sender) {
    playSoundEffect("Click");
    Director::getInstance()->replaceScene(TransitionSlideInR::create(SCENE_TRANSITION_TIME, CountDown::createScene()));
}