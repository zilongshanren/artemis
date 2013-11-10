#include "Velocity.h"

Velocity::Velocity()
	: _velocity(0.0f)
{

}

Velocity::Velocity( float velocity )
	: _velocity(velocity)
{

}

float Velocity::getVelocity() const
{
	return _velocity;
}

void Velocity::setVelocity( float velocity )
{
	this->_velocity = velocity;
}

void Velocity::addVelocity( float velocity )
{
	this->_velocity += velocity;
}
