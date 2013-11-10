#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

// artemis
#include "include\Component.h"

// Ãû³Æ£º×ª»»
class Transform : public artemis::Component
{
public:
	Transform();
	Transform(float x, float y);
	Transform(float x, float y, float rotation);
	void addX(float x);
	void addY(float y);
	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	void setLocation(float x, float y);
	float getRotation() const;
	void setRotation(float rotation);
	void addRotation(float angle);
	float getRotationAsRadians() const;

private:
	float _x;
	float _y;
	float _rotation;
};


#endif // __TRANSFORM_H__