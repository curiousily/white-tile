/*
 * Converter.h
 *
 *  Created on: Feb 5, 2014
 *      Author: vini
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Converter {
public:

	static std::string toString(int value) {
		return Value(value).asString();
	}
    
    static std::string toString(float value) {
		return Value(value).asString();
	}

	static int toInt(std::string value) {
		return Value(value).asInt();
	}
    
    static float toFloat(std::string value) {
        return Value(value).asFloat();
    }

private:
	Converter() {
	}
};

#endif /* CONVERTER_H_ */
