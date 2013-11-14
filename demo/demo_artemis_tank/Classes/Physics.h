#ifndef __PHYSCIS_H__
#define __PHYSCIS_H__

// artemis
#include "Component.h"

// cocos2dx
#include "cocos2d.h"

// √˚≥∆£∫ŒÔ¿Ì 
class Physics : public artemis::Component 
{
public:
	Physics(cocos2d::PhysicsBody* body);
	virtual ~Physics();

public:
	float getX() const;
	float getY() const;

	float getRotation() const;
	void addRotation(float angle);

	void setLocation(float x, float y);
	float getRotationAsRadians() const;
	void setForce(float xf, float yf);

	cocos2d::PhysicsBody* getBody() const;

private:
	cocos2d::PhysicsBody* _body;

};


#endif // __PHYSCIS_H__