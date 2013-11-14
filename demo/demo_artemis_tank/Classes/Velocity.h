#ifndef __VELOCITY_H__
#define __VELOCITY_H__

// artemis
#include "Component.h"

// Ãû³Æ£ºÏòÁ¿ 
class Velocity : public artemis::Component
{
public:
	Velocity();
	Velocity(float velocity);

public:

	float getVelocity() const;
	void setVelocity(float velocity);
	void addVelocity(float velocity);

private:
	float _velocity;
};


#endif // __VELOCITY_H__