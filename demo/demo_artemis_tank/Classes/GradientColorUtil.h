#ifndef __GRADIENT_COLOR_UTIL_H__
#define __GRADIENT_COLOR_UTIL_H__

#include "ccTypes.h"
class GradientColorUtil
{
public:
	// percent:[0, 100]
	static cocos2d::Color3B getGradientColor(float percent);

private:
	static cocos2d::Color3B START_COLOR;
	static cocos2d::Color3B END_COLOR  ;
};

#endif // __GRADIENT_COLOR_UTIL_H__
