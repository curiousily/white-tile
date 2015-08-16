//
//  PauseLayer.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#include "PauseLayer.h"

bool PauseLayer::init() {
    if(!LayerColor::initWithColor(PAUSE_BACKGROUND_COLOR))
    {
        return false;
    }
    addBackground(this);
    
    auto resumeButton = MenuItemSprite::create(sprite("ResumeButtonNormal"), sprite("ResumeButtonPressed"), [=](Ref* sender) {
        playSoundEffect("Click");
        EventCustom event("ResumeGame");
        _eventDispatcher->dispatchEvent(&event);
        removeFromParent();
    });
    resumeButton->setPosition(Point(VisibleRect::center().x, 1920 - 841));
    

    auto rotationSequence = Sequence::create( RotateTo::create(DEFAULT_ANIMATION_TIME / 2, TILE_ROTATION_DEGREE), RotateTo::create(DEFAULT_ANIMATION_TIME, -TILE_ROTATION_DEGREE), RotateTo::create(DEFAULT_ANIMATION_TIME / 2, 0.0f), NULL);
    auto scalingSequence = Sequence::create(ScaleTo::create(DEFAULT_ANIMATION_TIME, 1.1f), ScaleTo::create(DEFAULT_ANIMATION_TIME, 1.0f), NULL);
    resumeButton->runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 3), Spawn::create(rotationSequence, scalingSequence, NULL), NULL)));
    
    auto exitButton = MenuItemSprite::create(sprite("ExitButtonNormal"), sprite("ExitButtonPressed"), [=](Ref* sender) {
        playSoundEffect("Click");
        _eventDispatcher->removeAllEventListeners();
        Director::getInstance()->replaceScene(TransitionSlideInL::create(SCENE_TRANSITION_TIME, MainMenu::createScene()));
    });
    exitButton->setPosition(Point(VisibleRect::center().x, 1920 - 1083));
    
    auto menu = Menu::create(resumeButton, exitButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    runAction(RepeatForever::create(Sequence::create(DelayTime::create(DEFAULT_ANIMATION_TIME * 12), CallFunc::create([=] () {
        playSoundEffect("Giggle");
    }) , NULL)));
    
    return true;
}