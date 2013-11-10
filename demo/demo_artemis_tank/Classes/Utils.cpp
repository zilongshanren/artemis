#include "Utils.h"

// C++
#include <math.h>

// game
#include "TrigLUT.h"

float Utils::getRotatedX( float currentX, float currentY, float pivotX, float pivotY, float angleDegrees )
{
	float x = currentX - pivotX;
	float y = currentY - pivotY;
	float xr = (x * TrigLUT::cosDeg(angleDegrees)) - (y * TrigLUT::sinDeg(angleDegrees));
	return xr + pivotX;
}

float Utils::getRotatedY( float currentX, float currentY, float pivotX, float pivotY, float angleDegrees )
{
	float x = currentX - pivotX;
	float y = currentY - pivotY;
	float yr = (x * TrigLUT::sinDeg(angleDegrees)) + (y * TrigLUT::cosDeg(angleDegrees));
	return yr + pivotY;
}

float Utils::angleInDegrees( float originX, float originY, float targetX, float targetY )
{
	return atan2(targetY-originY, targetX-originX);
}

float Utils::shouldRotateCounterClockwise( float angleFrom, float angleTo )
{		
	int diff = int(angleFrom - angleTo) % 360;
	return diff > 0 ? diff < 180 : diff < -180;
}

float Utils::euclideanDistance( float x1, float y1, float x2, float y2 )
{
	float a = x1 - x2;
	float b = y1 - y2;

	return (float)sqrt(a*a + b*b);
}

