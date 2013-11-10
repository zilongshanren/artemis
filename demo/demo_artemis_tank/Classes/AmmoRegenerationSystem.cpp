#include "AmmoRegenerationSystem.h"

AmmoRegenerationSystem::AmmoRegenerationSystem()
{
	addComponentType<Ammo>();
}

void AmmoRegenerationSystem::initialize()
{
	_ammoMapper.init(*world);

	this->setAutoRepeat(true);
	this->start(100);
}

void AmmoRegenerationSystem::processEntities( artemis::ImmutableBag<artemis::Entity*> & bag, float accumulatedDelta )
{
	for (int i = 0; i < bag.getCount(); ++i)
	{
		auto ammo = _ammoMapper.get(*bag.get(i));
		ammo->addAmmo(1.0f);
	}
}
