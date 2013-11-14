#ifndef __AMMO_REGENERATION_SYSTEM_H__
#define __AMMO_REGENERATION_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "DelayedEntitySystem.h"

// game
#include "Ammo.h"

// 名称：弹药再生系统
class AmmoRegenerationSystem : public artemis::DelayedEntitySystem
{
public:
	AmmoRegenerationSystem();

public:
	virtual void initialize() override;
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag, float accumulatedDelta) override;

private:
	artemis::ComponentMapper<Ammo> _ammoMapper;
};

#endif // __AMMO_REGENERATION_SYSTEM_H__