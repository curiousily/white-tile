#include "Random.h"

float Random::between(float min, float max) {
	return (((float) arc4random() / 0xFFFFFFFFu) * (max - min)) + min;
}

bool Random::hasLuck(int luckPercent) {
    return Random::between(0, 100) < luckPercent;
}