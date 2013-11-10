#ifndef __PLAYER_ENTITY_SYSTEM_H__
#define __PLAYER_ENTITY_SYSTEM_H__

// artemis
#include "include\EntitySystem.h"

class PlayerEntitySystem : public artemis::EntitySystem
{
public:
	PlayerEntitySystem();

protected: // artemis
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) override = 0;
	virtual bool checkProcessing() override = 0;

protected:
	void ensurePlayerEntity();

protected:
	artemis::Entity* _player;

protected:
	static const float MAX_VELOCITY;
	static const float THRUST;
	static const float TURN_THRUST;
	static const float MAX_TURN_VELOCITY;
	static const float MAX_MOTOR_TORQUE;
	static const float RECOIL_SPEED;
	static const float RECOIL_RECOVER_SPEED;
	static const int   RECOIL_TARGET_OFFSET;
};


#endif // __PLAYER_ENTITY_SYSTEM_H__