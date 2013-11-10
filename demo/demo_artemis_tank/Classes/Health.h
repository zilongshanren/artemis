#ifndef __HEALTH_H__
#define __HEALTH_H__

// artemis
#include "include\Component.h"

// Ãû³Æ£ºÉúÃüÖµ
class Health : public artemis::Component
{
public:
	Health(float health);
	Health(float health, float maximumHealth);

public:
	float getHealth() const;
	float getMaximumHealth() const;
	float getHealthStatus() const;
	void addDamage(float damage);
	bool isAlive() const;

private:
	float _health;
	float _maximumHealth;
};


#endif // __HEALTH_H__