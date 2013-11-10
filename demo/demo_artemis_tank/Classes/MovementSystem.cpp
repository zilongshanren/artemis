#include "MovementSystem.h"

// game
#include "TrigLUT.h"

MovementSystem::MovementSystem()
{
	addComponentType<Transform>();
	addComponentType<Velocity>();
}

void MovementSystem::initialize()
{
	_transformMapper.init(*world);
	_velocityMapper.init(*world);
}

void MovementSystem::processEntity(artemis::Entity &e) 
{
	auto t = _transformMapper.get(e);
	auto velocity = _velocityMapper.get(e);

	float r = t->getRotationAsRadians();
	float v = velocity->getVelocity();

	float xn = t->getX() + (TrigLUT::cos(r) * v * world->getDelta());
	float yn = t->getY() + (TrigLUT::sin(r) * v * world->getDelta());

	t->setLocation(xn, yn);
}

bool MovementSystem::checkProcessing() 
{
	return true;
}