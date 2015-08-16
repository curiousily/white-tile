//
//  PauseLayer.h
//  whitetile
//
//  Created by Venelin Valkov on 4/28/14.
//
//

#ifndef __whitetile__PauseLayer__
#define __whitetile__PauseLayer__

#include "cocos2d.h"
#include "AssetManager.h"
#include "Constants.h"
#include "Converter.h"
#include "Formatter.h"
#include "MainMenuScene.h"

USING_NS_CC;

class PauseLayer : public cocos2d::LayerColor, public AssetManager
{
public:
    
    bool init() override;
    
    const char* getResourceDirectory() override {
        return "Pause";
    }

CREATE_FUNC(PauseLayer);

};

#endif /* defined(__whitetile__PauseLayer__) */
