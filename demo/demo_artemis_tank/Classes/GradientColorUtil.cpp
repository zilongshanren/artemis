#include "GradientColorUtil.h"

USING_NS_CC;

cocos2d::Color3B GradientColorUtil::getGradientColor( float percent )
{
	static Color3B S = Color3B::GREEN;
	static Color3B E = Color3B::RED;

	Color3B ret;

	percent = MAX(percent, 0.0f);
	percent = MIN(percent, 100.0f);
	percent /= 100.0f;
	ret.r = E.r + (S.r - E.r) * percent;
	ret.g = E.g + (S.g - E.g) * percent;
	ret.b = E.b + (S.b - E.b) * percent;
	return ret;
}
