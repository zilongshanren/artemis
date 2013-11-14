#include "PlayerTankTowerSystem.h"

// artemis
#include "Entity.h"
#include "EntitySystem.h"
#include "SystemManager.h"
#include "TagManager.h"
#include "World.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game 
#include "Constants.h"
#include "EntityFactory.h"
#include "TrigLUT.h"
#include "Utils.h"

PlayerTankTowerSystem::PlayerTankTowerSystem(DPadLayer* input)
	: _recoil(false)
	, _shoot(false)
	, _turnLeft(false)
	, _turnRight(false)
{
	CCAssert(input, "input should not be nullptr.");
	_input = input;

	addComponentType<Ammo>();
	addComponentType<Dirty>();
	addComponentType<Physics>();
	addComponentType<Tower>();
	addComponentType<Transform>();
	addComponentType<TurnFactor>();
	addComponentType<Velocity>();
}

void PlayerTankTowerSystem::initialize()
{
	_input->addListener(this);

	_ammoMapper.init(*world);
	_dirtyMapper.init(*world);
	_physicsMapper.init(*world);
	_towerMapper.init(*world);
	_transformMapper.init(*world);
	_turnFactorMapper.init(*world);
	_velocityMapper.init(*world);

	ensurePlayerEntity();
}

void PlayerTankTowerSystem::processEntities( artemis::ImmutableBag<artemis::Entity*>& bag )
{
	ensurePlayerEntity();
	if (nullptr != _player)
	{
		updatePlayer(*_player);
	}
}

bool PlayerTankTowerSystem::checkProcessing()
{
	return true;
}

void PlayerTankTowerSystem::updatePlayer( artemis::Entity& e )
{
	auto ammo    = _ammoMapper.get(e);
	auto dirty   = _dirtyMapper.get(e);
	auto physics = _physicsMapper.get(e);
	auto tf      = _turnFactorMapper.get(e);
	auto tower   = _towerMapper.get(e);
	auto v       = _velocityMapper.get(e);

	updateTowerRotation(tower, physics);

	updateRecoil(tower);

	if (_shoot && ammo->hasAmmo(10)) 
	{
		_shoot = false;
		_recoil = true;

		auto angle = tower->getRotation()+physics->getRotation();
		// Create bullets for both barrels.
		{
			float x = Utils::getRotatedX(physics->getX() + 75, physics->getY() - 10, physics->getX(), physics->getY(), angle);
			float y = Utils::getRotatedY(physics->getX() + 75, physics->getY() - 10, physics->getX(), physics->getY(), angle);
			EntityFactory::createBullet(*world, x, y, angle, e).refresh();
		}

		{
			float x = Utils::getRotatedX(physics->getX() + 75, physics->getY() + 10, physics->getX(), physics->getY(), angle);
			float y = Utils::getRotatedY(physics->getX() + 75, physics->getY() + 10, physics->getX(), physics->getY(), angle);
			EntityFactory::createBullet(*world, x, y, angle, e).refresh();
		}

		// apply force to moving tank.
		float counterRotation = angle+180;
		float force = 2000.0f;
		// TODO： 坦克发炮后，炮台的后坐力效果 
	    //	physics->setForce(force*TrigLUT::cosDeg(counterRotation), force*TrigLUT::sinDeg(counterRotation));

		// add sound.
		EntityFactory::createSound(*world, "sounds/shoot.ogg", SoundType::SE).refresh();

		ammo->reduceBy(10);
		dirty->setDirty(true);
	}
}

void PlayerTankTowerSystem::updateTowerRotation( Tower* tower, Physics* p )
{
	if (_turnLeft)
	{
		tower->addRotation(tower->getTurnThrust());
	}
	else if (_turnRight)
	{
		tower->addRotation(-tower->getTurnThrust());
	}
	else 
	{
		float mouseX = _input->getMouse().x;
		float mouseY = _input->getMouse().y;
		float r = Utils::angleInDegrees(p->getX(), p->getY(), mouseX, mouseY);
		if (int(abs(r-tower->getRotation()))%360 > 2)
		{
			if (Utils::shouldRotateCounterClockwise(r, tower->getRotation())) 
			{
				tower->addRotation(world->getDelta() * 0.1f);
			}
			else
			{
				tower->addRotation(world->getDelta() * -0.1f);
			}
		}
	}
}

void PlayerTankTowerSystem::updateRecoil( Tower* tower )
{
	float recoilOffset = tower->getRecoil();
	if (_recoil)
	{
		recoilOffset += world->getDelta() * RECOIL_SPEED;

		if (recoilOffset > RECOIL_TARGET_OFFSET)
		{
			recoilOffset = RECOIL_TARGET_OFFSET;
			_recoil = false;
		}

		tower->setRecoil(recoilOffset);
	}
	else if (recoilOffset > 0)
	{
		recoilOffset -= (float) world->getDelta() * RECOIL_RECOVER_SPEED;
		if (recoilOffset < 0)
			recoilOffset = 0;
		tower->setRecoil(recoilOffset);
	}
}

void PlayerTankTowerSystem::onTowerJoyStickUpdate( cocos2d::Node* sender, float angle, cocos2d::Point direction, float power )
{
	if (_player)
	{
		if (direction.x > 0) // turn right
		{
			_turnLeft  = false;
			_turnRight = true;
		}
		else // turn left
		{
			_turnLeft  = true;
			_turnRight = false;
		}
	}	
}

void PlayerTankTowerSystem::onTowerJoyStickDeactivated( cocos2d::Node* sender )
{
	_shoot     = true;
	_turnLeft  = false;
	_turnRight = false;
}
