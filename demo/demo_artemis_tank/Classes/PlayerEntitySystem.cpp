#include "PlayerEntitySystem.h"

// artemis
#include "include/Entity.h"
#include "include/World.h"

// game
#include "Constants.h"

PlayerEntitySystem::PlayerEntitySystem()
	: _player(nullptr)
{

}

void PlayerEntitySystem::ensurePlayerEntity()
{
	if (nullptr == _player || !_player->isActive())
	{
		_player = &(world->getTagManager()->getEntity(Constants::Groups::PLAYER));
	}
}

const float PlayerEntitySystem::MAX_VELOCITY         = 0.16f;
const float PlayerEntitySystem::THRUST               = 0.00012f;
const float PlayerEntitySystem::TURN_THRUST          = 0.05f;
const float PlayerEntitySystem::MAX_TURN_VELOCITY    = M_PI;
const float PlayerEntitySystem::MAX_MOTOR_TORQUE     = 20000.0f;
const float PlayerEntitySystem::RECOIL_SPEED         = 0.2f;
const float PlayerEntitySystem::RECOIL_RECOVER_SPEED = 0.02f;
const int   PlayerEntitySystem::RECOIL_TARGET_OFFSET = 20;

