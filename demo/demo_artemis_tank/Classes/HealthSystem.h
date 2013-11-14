#ifndef __HEALTH_SYSTEM_H__
#define __HEALTH_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntityProcessingSystem.h"

// game
#include "Health.h"

class HealthSystem : public artemis::EntityProcessingSystem
{
public:
	HealthSystem();

public:
	virtual void initialize() override;
	virtual void processEntity(artemis::Entity& e) override;

private:
	artemis::ComponentMapper<Health> _healthMapper;
};


#endif // __HEALTH_SYSTEM_H__