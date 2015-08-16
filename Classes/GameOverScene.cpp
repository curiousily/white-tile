//
//  GameOverScene.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/12/14.
//
//

#include "GameOverScene.h"


Scene* GameOver::createScene() {
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init() {
    
    if(!LayerColor::initWithColor(MENU_BACKGROUND_COLOR)) {
        return false;
    }
    
    gameMode = static_cast<GameMode>(UserDefault::getInstance()->getIntegerForKey("mode", GameMode::ARCADE));
    
    switch (gameMode) {
        case GameMode::ARCADE:
            addChild(sprite("ArcadeMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
            break;
            
        case GameMode::TIME_ATTACK:
            addChild(sprite("TimeAttackMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
            break;
            
        default:
            addChild(sprite("ZenMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
    }
    
    if(UserDefault::getInstance()->getBoolForKey(IS_WIN_KEY)) {
        showWinScreen();
    } else {
        playSoundEffect("Fail");
        label("FAILED")->size(MENU_FONT_SIZE * 3)->color(TIME_ATTACK_TEXT_COLOR)->position(VisibleRect::center())->addTo(this);
    }
    
    auto homeButton = MenuItemSprite::create(sprite("HomeButtonNormal"), sprite("HomeButtonPressed"), [=] (Ref* sender) {
        playSoundEffect("Click");
        Director::getInstance()->replaceScene(TransitionSlideInL::create(SCENE_TRANSITION_TIME, MainMenu::createScene()));
    });
    homeButton->setPosition(Point(202, 1920 - 1600));

    auto retryButton = MenuItemSprite::create(sprite("RetryButtonNormal"), sprite("RetryButtonPressed"), [=] (Ref* sender) {
        playSoundEffect("Click");
        Director::getInstance()->replaceScene(TransitionSlideInL::create(SCENE_TRANSITION_TIME, CountDown::createScene()));
    });
    retryButton->setPosition(Point(545, 1920 - 1600));
    
#if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

    auto shareButton = MenuItemSprite::create(sprite("ShareButtonNormal"), sprite("ShareButtonPressed"), [=] (Ref*) {
        playSoundEffect("Click");
        NativeUtils::share();
    });
    shareButton->setPosition(Point(886, 1920 - 1600));
    
    auto menu = Menu::create(homeButton, retryButton, shareButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
#else
    auto menu = Menu::create(homeButton, retryButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
#endif
    return true;
}

void GameOver::showWinScreen() {
    scoreBox = sprite("ScoreBox", VisibleRect::center());
    addChild(scoreBox);
    
    float score = UserDefault::getInstance()->getFloatForKey(SCORE_KEY);
    
    std::string highScore;
    
    std::string scoreText;
    
    switch (gameMode) {
        case GameMode::ARCADE:
            addChild(sprite("ArcadeMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
            NativeUtils::submitScore(ARCADE_MODE_LEADERBOARD, (int) score);
            scoreText = Value((int) score).asString();
            if(HighScoreManager::isHigherScore(ARCADE_HIGH_SCORE_KEY, score)) {
                onNewHighScore(ARCADE_HIGH_SCORE_KEY, score);
                highScore = scoreText;
            } else {
                highScore = Value((int) HighScoreManager::getHighScore(ARCADE_HIGH_SCORE_KEY)).asString();
            }
            break;
            
        case GameMode::TIME_ATTACK:
            addChild(sprite("TimeAttackMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
            NativeUtils::submitScore(TIME_ATTACK_MODE_LEADERBOARD, (int) (score * 1000));
            scoreText = Formatter::toString("%.3f", score);
            if(HighScoreManager::isLowerScore(TIME_ATTACK_HIGH_SCORE_KEY, score)) {
                onNewHighScore(TIME_ATTACK_HIGH_SCORE_KEY, score);
                highScore = scoreText;
            } else {
                highScore = Formatter::toString("%.3f", HighScoreManager::getHighScore(TIME_ATTACK_HIGH_SCORE_KEY));
            }
            break;
            
        default:
            addChild(sprite("ZenMode", Point(VisibleRect::top().x, VisibleRect::top().y - 200)));
            NativeUtils::submitScore(ZEN_MODE_LEADERBOARD, (int) score);
            scoreText = Value((int) score).asString();
            if(HighScoreManager::isHigherScore(ZEN_HIGH_SCORE_KEY, score)) {
                onNewHighScore(ZEN_HIGH_SCORE_KEY, score);
                highScore = scoreText;
            } else {
                highScore = Value((int) HighScoreManager::getHighScore(ZEN_HIGH_SCORE_KEY)).asString();
            }
    }
    
    label(scoreText.c_str())->color(Color3B::WHITE)->position(Point(scoreBox->getPositionX() + 170, scoreBox->getPositionY() + 100))->addTo(this);
    
    
    label(highScore.c_str())->color(Color3B::WHITE)->position(Point(scoreBox->getPositionX() + 170, scoreBox->getPositionY() - 80))->addTo(this);
}

void GameOver::onNewHighScore(const char* highScoreKey, float score) {
    HighScoreManager::saveHighScore(highScoreKey, score);
    playSoundEffect("Success");
    addChild(sprite("BestScore", Point(VisibleRect::center().x, scoreBox->getPositionY() + scoreBox->getContentSize().height / 2 + 80)));
}