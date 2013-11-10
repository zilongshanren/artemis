#include "Health.h"
#include "CCStdC.h"

Health::Health( float health )
	: _health(health)
	, _maximumHealth(health)
{

}

Health::Health( float health, float maximumHealth )
	: _health( MIN(health, maximumHealth) )
	, _maximumHealth(maximumHealth)
{

}

float Health::getHealth() const
{
	return _health;
}

float Health::getMaximumHealth() const
{
	return _maximumHealth;
}

float Health::getHealthStatus() const
{
	return _health/_maximumHealth*100.0f;
}

void Health::addDamage( float damage )
{
	_health -= damage;
	if (_health < 0)
	{
		_health = 0;
	}
}

bool Health::isAlive() const
{
	return _health > 0;
}
