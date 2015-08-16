#ifndef RANDOM_H_
#define RANDOM_H_

#include "cocos2d.h"

USING_NS_CC;

class Random {

public:
    
    /**
     * Inclusive [min, max]
     */
	static float between(float min, float max);
    
    /**
     * Return true if the random value [0, 100] is lower than luckPercent
     */
    static bool hasLuck(int luckPercent);
    
	template<typename T>
	static T choose(std::vector<T> value) {
		int size = value.size();
		int index = Random::between(0, size - 1);
		return value[index];
	}
};

#endif /* RANDOM_H_ */
