#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "SoundManager.h"
#include "SplashScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto scene = MainMenu::createScene();
    director->runWithScene(scene);
#else
    auto scene = Splash::createScene();
    director->runWithScene(scene);
#endif


    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    EventCustom event("PauseGame");
    eventDispatcher->dispatchEvent(&event);

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeAllEffects();


    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
