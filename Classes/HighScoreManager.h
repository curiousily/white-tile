//
//  HighScoreManager.h
//  whitetile
//
//  Created by Venelin Valkov on 4/30/14.
//
//

#ifndef __whitetile__HighScoreManager__
#define __whitetile__HighScoreManager__

#include "cocos2d.h"
#include "Converter.h"

USING_NS_CC;

class HighScoreManager {
    
public:
    
    static bool isHigherScore(const char* highScoreKey, float score) {
        
        auto db = UserDefault::getInstance();
        auto oldScore = db->getFloatForKey(highScoreKey, score - 1.0f);
        return score > oldScore;
    }
    static bool isLowerScore(const char* highScoreKey, float score) {
        auto db = UserDefault::getInstance();
        auto oldScore = db->getFloatForKey(highScoreKey, score + 1.0f);
        return score < oldScore;
    }
    
    static void saveHighScore(const char* highScoreKey, float score) {
        auto db = UserDefault::getInstance();
        db->setFloatForKey(highScoreKey, score);
        db->flush();

    }
    
    static float getHighScore(const char* highScoreKey) {
        auto db = UserDefault::getInstance();
        return db->getFloatForKey(highScoreKey);
    }
    
};

#endif /* defined(__whitetile__HighScoreManager__) */
