#ifndef __PLAYER_TANK_MOVEMENT_SYSTEM_H__
#define __PLAYER_TANK_MOVEMENT_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntitySystem.h"

// game
#include "Ammo.h"
#include "DPadLayer.h"
#include "Physics.h"
#include "PlayerEntitySystem.h"
#include "Tower.h"
#include "Transform.h"
#include "TurnFactor.h"
#include "Velocity.h"

class PlayerTankMovementSystem
	: public PlayerEntitySystem
	, public DPadListener
{
public:
	PlayerTankMovementSystem(DPadLayer* input);

public: // artemis
	virtual void initialize() override;
	
protected: // artemis
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) override;
	virtual bool checkProcessing() override;

protected: // d-pad
	virtual void onTankJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) override;
	virtual void onTankJoyStickActivated(cocos2d::Node* sender)   override { CC_UNUSED_PARAM(sender); }
	virtual void onTankJoyStickDeactivated(cocos2d::Node* sender) override;

	virtual void onTowerJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) override { };
	virtual void onTowerJoyStickActivated(cocos2d::Node* sender)   override { CC_UNUSED_PARAM(sender); }
	virtual void onTowerJoyStickDeactivated(cocos2d::Node* sender) override { CC_UNUSED_PARAM(sender); }

private:
	void updatePlayer(artemis::Entity& e);
	void updateMoving(artemis::Entity& e, float delta);
	void updateTurning(Physics* physics, Velocity* v, TurnFactor* tf, float delta);

private:
	DPadLayer* _input;

	float      _velocity;

	bool       _forward;
	bool       _reverse;
	bool       _turnRight;
	bool       _turnLeft;

	bool       _moving;
	bool       _turning;

	bool       _recoil;
	bool       _shoot;

	artemis::ComponentMapper<Transform>  _transformMapper;
	artemis::ComponentMapper<Velocity>   _velocityMapper;
	artemis::ComponentMapper<TurnFactor> _turnFactorMapper;
	artemis::ComponentMapper<Tower>      _towerMapper;
	artemis::ComponentMapper<Physics>    _collidableMapper;
};


#endif // __PLAYER_TANK_MOVEMENT_SYSTEM_H__