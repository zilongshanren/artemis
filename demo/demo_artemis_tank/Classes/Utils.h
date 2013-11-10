#ifndef __UTILS_H__
#define __UTILS_H__

class Utils
{
public:
	static float getRotatedX(float currentX, float currentY, float pivotX, float pivotY, float angleDegrees);
	static float getRotatedY(float currentX, float currentY, float pivotX, float pivotY, float angleDegrees);

	static float angleInDegrees(float originX, float originY, float targetX, float targetY);
	static float shouldRotateCounterClockwise(float angleFrom, float angleTo);

	static float euclideanDistance(float x1, float y1, float x2, float y2);
};


#endif // __UTILS_H__