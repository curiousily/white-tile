//
//  AnimatedNode.cpp
//  whitetile
//
//  Created by Venelin Valkov on 4/27/14.
//
//

#include "AnimatedNode.h"

AnimatedNode* AnimatedNode::create(const std::string &animationFile) {
    auto animatedNode = new AnimatedNode();
    animatedNode->initWithFile(animationFile);
    animatedNode->autorelease();
    return animatedNode;
}

bool AnimatedNode::initWithFile(const std::string &animationFile) {
    this->animationFile = animationFile;
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(Formatter::toString("Scenes/Game/%s.plist", animationFile.c_str()));
    animatedSprite = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(Formatter::toString("%s1.png", animationFile.c_str())));
    if(!SpriteBatchNode::initWithFile(Formatter::toString("Scenes/Game/%s.png", animationFile.c_str()), 30)) {
        return false;
    }
    addChild(animatedSprite);
    return true;
}

void AnimatedNode::play(float frameDelay) {
    play(nullptr, frameDelay);
}

void AnimatedNode::play(const std::function<void ()> &onDone, float frameDelay) {
    auto cache = SpriteFrameCache::getInstance();
    auto spriteFrames = Vector<SpriteFrame*>();
    
    for(int i = 1; i <= INT_MAX; ++i)
    {
        auto spriteFrame = cache->getSpriteFrameByName(Formatter::toString("%s%d.png", animationFile.c_str(), i));
        if (spriteFrame != nullptr) {
            spriteFrames.pushBack(spriteFrame);
        } else {
            break;
        }
    }
    auto animation = Animation::createWithSpriteFrames(spriteFrames, frameDelay);
    animatedSprite->runAction(Sequence::create(Animate::create(animation), CallFunc::create(onDone), NULL));
}

void AnimatedNode::stop() {
    animatedSprite->stopAllActions();
}