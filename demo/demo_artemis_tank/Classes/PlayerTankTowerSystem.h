#ifndef __PLAYER_TANK_TOWER_SYSTEM_H__
#define __PLAYER_TANK_TOWER_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\EntitySystem.h"

// game
#include "Ammo.h"
#include "Dirty.h"
#include "DPadLayer.h"
#include "Physics.h"
#include "PlayerEntitySystem.h"
#include "Tower.h"
#include "Transform.h"
#include "TurnFactor.h"
#include "Velocity.h"

class PlayerTankTowerSystem 
	: public PlayerEntitySystem
	, public DPadListener
{
public:
	PlayerTankTowerSystem(DPadLayer* input);

public: // artemis
	virtual void initialize() override;

protected: // artemis
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) override;
	virtual bool checkProcessing() override;

protected: // d-pad
	virtual void onTankJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) override { CC_UNUSED_PARAM(sender); }
	virtual void onTankJoyStickActivated(cocos2d::Node* sender)   override { CC_UNUSED_PARAM(sender); }
	virtual void onTankJoyStickDeactivated(cocos2d::Node* sender) override { CC_UNUSED_PARAM(sender); }

	virtual void onTowerJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) override;
	virtual void onTowerJoyStickActivated(cocos2d::Node* sender)   override { CC_UNUSED_PARAM(sender); }
	virtual void onTowerJoyStickDeactivated(cocos2d::Node* sender) override;

protected:
	void updatePlayer(artemis::Entity& e);

private:
	void updateTowerRotation(Tower* tower, Physics* p);
	void updateRecoil(Tower* tower);

private:
	DPadLayer*       _input;
	bool             _recoil;
	bool             _shoot;
	bool             _turnLeft;
	bool             _turnRight;

	artemis::ComponentMapper<Ammo>       _ammoMapper;
	artemis::ComponentMapper<Dirty>      _dirtyMapper;
	artemis::ComponentMapper<Physics>    _physicsMapper;
	artemis::ComponentMapper<Tower>      _towerMapper;
	artemis::ComponentMapper<Transform>  _transformMapper;
	artemis::ComponentMapper<TurnFactor> _turnFactorMapper;
	artemis::ComponentMapper<Velocity>   _velocityMapper;
};

#endif // __PLAYER_TANK_TOWER_SYSTEM_H__
