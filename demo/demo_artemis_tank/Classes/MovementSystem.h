#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntityProcessingSystem.h"

// game
#include "Transform.h"
#include "Velocity.h"

class MovementSystem : public artemis::EntityProcessingSystem
{
public:
	MovementSystem();

public:
	virtual void initialize() override;
	virtual void processEntity(artemis::Entity &e) override;
	virtual bool checkProcessing() override;

private:

	artemis::ComponentMapper<Transform> _transformMapper;
	artemis::ComponentMapper<Velocity>  _velocityMapper;
};


#endif // __MOVEMENT_SYSTEM_H__