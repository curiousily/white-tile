//
//  AnimatedNode.h
//  whitetile
//
//  Created by Venelin Valkov on 4/27/14.
//
//

#ifndef __whitetile__AnimatedNode__
#define __whitetile__AnimatedNode__

#include "cocos2d.h"
#include "Formatter.h"

USING_NS_CC;

class AnimatedNode : public SpriteBatchNode {
    
public:
    static AnimatedNode* create(const std::string &animationFile);
    
    void play(const std::function<void ()> &onDone, float frameDelay = 0.2f);
    void play(float frameDelay = 0.2f);
    void stop();
    
private:
    
    Sprite* animatedSprite;
    std::string animationFile;
    
    bool initWithFile(const std::string &animationFile);
    
};

#endif /* defined(__whitetile__AnimatedNode__) */
