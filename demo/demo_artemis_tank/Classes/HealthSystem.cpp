#include "HealthSystem.h"

HealthSystem::HealthSystem()
{
	this->addComponentType<Health>();
}

void HealthSystem::initialize()
{
	_healthMapper.init(*world);
}

void HealthSystem::processEntity( artemis::Entity& e )
{
	auto health = _healthMapper.get(e);

	if(!health->isAlive())
	{
		world->deleteEntity(e);
	}
}
