#include "PlayerTankMovementSystem.h"

// artemis
#include "include/Entity.h"
#include "include/EntitySystem.h"
#include "include/SystemManager.h"
#include "include/TagManager.h"
#include "include/World.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game 
#include "Constants.h"
#include "EntityFactory.h"
#include "TrigLUT.h"
#include "Utils.h"

PlayerTankMovementSystem::PlayerTankMovementSystem(DPadLayer* input)
	:  _velocity(0.0f)
	,  _forward(false)
	,  _reverse(false)
	,  _turnRight(false)
	,  _turnLeft(false)
	,  _moving(false)
	,  _turning(false)
	,  _recoil(false)
	,  _shoot(false)
{
	CCAssert(input, "input should not be nullptr.");
	_input = input;

	addComponentType<Transform>();
	addComponentType<Velocity>();
	addComponentType<TurnFactor>();
	addComponentType<Tower>();
	addComponentType<Physics>();
}

void PlayerTankMovementSystem::initialize()
{
	_input->addListener(this);

	_transformMapper.init(*world);
	_velocityMapper.init(*world);
	_turnFactorMapper.init(*world);
	_towerMapper.init(*world);
	_collidableMapper.init(*world);
	
	ensurePlayerEntity();
}

void PlayerTankMovementSystem::processEntities( artemis::ImmutableBag<artemis::Entity*>& bag )
{
	ensurePlayerEntity();

	if (nullptr != _player)
	{
		updatePlayer(*_player);
	}
}

bool PlayerTankMovementSystem::checkProcessing()
{
	return true;
}

void PlayerTankMovementSystem::updatePlayer( artemis::Entity& e )
{
	auto v  = _velocityMapper.get(e);
	auto tf = _turnFactorMapper.get(e);
	auto c  = _collidableMapper.get(e);

	updateMoving(e, world->getDelta());
	updateTurning(c, v, tf, world->getDelta());
}

void PlayerTankMovementSystem::updateMoving( artemis::Entity& e, float delta )
{
	auto physics = _collidableMapper.get(e);

	if(_forward) 
	{
		float ax = (TrigLUT::cosDeg(physics->getRotation()) * delta)*10000.0f;
		float ay = (TrigLUT::sinDeg(physics->getRotation()) * delta)*10000.0f;

		_velocity += delta * 0.5f;
		if(_velocity > 1.25f) 
		{
			_velocity = 1.25f;
		}
		physics->getBody()->setVelocity(Point(_velocity*ax, _velocity*ay));
	} 
	else if(_velocity > 0) 
	{
		_velocity -= delta;
		if(_velocity < 0) 
		{
			_velocity = 0;
		}
	}

	if(_reverse) 
	{
		float ax = (TrigLUT::cosDeg(physics->getRotation()) * delta)*10000.0f;
		float ay = (TrigLUT::sinDeg(physics->getRotation()) * delta)*10000.0f;

		_velocity -= delta * 0.25f;
		if(_velocity < -1) 
		{
			_velocity = -1;
		}
		physics->getBody()->setVelocity(Point(_velocity*ax, _velocity*ay));
	}
	else if(_velocity < 0) 
	{
		_velocity += delta;
		if(_velocity > 0) 
		{
			_velocity = 0;
		}
	}
}

void PlayerTankMovementSystem::updateTurning( Physics* physic, Velocity* v, TurnFactor* tf, float delta )
{
	float turnFactor = tf->getFactor();

	if (_turnRight) 
	{
		turnFactor += delta * TURN_THRUST;
		if (turnFactor > MAX_TURN_VELOCITY) 
		{
			turnFactor = MAX_TURN_VELOCITY;
		}
		_turning = true;
	}
	else if (_turnLeft)
	{
		turnFactor -= delta * TURN_THRUST;
		if (turnFactor < -MAX_TURN_VELOCITY) 
		{
			turnFactor = -MAX_TURN_VELOCITY;
		}
		_turning = true;
	}

	// 恢复到原始角度用的 
	if (!_turnRight && !_turnLeft && _turning)
	{
		if (turnFactor > 0)
		{
			turnFactor -= delta * TURN_THRUST;
			if (turnFactor <= 0)
			{
				turnFactor = 0;
				_turning = false;
			}
		} 
		else 
		{
			turnFactor += delta * TURN_THRUST;
			if (turnFactor >= 0)
			{
				turnFactor = 0;
				_turning = false;
			}
		}
	}

	if (_turning) 
	{
		Point velocity;
		velocity.x = (TrigLUT::cosDeg(physic->getRotation()) * delta)*10000.0f;
		velocity.y = (TrigLUT::sinDeg(physic->getRotation()) * delta)*10000.0f;
		float lengthSq = velocity.getLengthSq()/MAX_MOTOR_TORQUE;
		
		if (lengthSq > 0.5f)
		{
			tf->setFactor(turnFactor*lengthSq/MAX_VELOCITY);

			if(_turnRight) 
			{
				physic->getBody()->setRotation(tf->getFactor());
			}
			else if(_turnLeft) 
			{
				physic->getBody()->setRotation(tf->getFactor());
			}
		}
	}

	tf->setFactor(turnFactor);
}

void PlayerTankMovementSystem::onTankJoyStickUpdate( cocos2d::Node* sender, float angle, cocos2d::Point direction, float power )
{
	auto dPad = (DPadLayer*)sender;
	auto key = dPad->getKeyCode();

	if (key == DPadKeyCode::UP || key == DPadKeyCode::UPLEFT || key == DPadKeyCode::UPRIGHT)
	{
		_forward   = true;
		_reverse   = false;
		_turnLeft  = false;
		_turnRight = false;
	}
	else if (key == DPadKeyCode::DOWN || key == DPadKeyCode::DOWNLEFT || key == DPadKeyCode::DOWNRIGHT) 
	{
		_reverse   = true;
		_forward   = false;
		_turnLeft  = false;
		_turnRight = false;
	}
	
	if (key == DPadKeyCode::LEFT) 
	{
		_turnLeft  = true;
		_turnRight = false;
	}
	
	if (key == DPadKeyCode::RIGHT) 
	{
		_turnLeft  = false;
		_turnRight = true;
	}
}

void PlayerTankMovementSystem::onTankJoyStickDeactivated( cocos2d::Node* sender )
{
	_forward   = false;
	_reverse   = false;
	_turnLeft  = false;
	_turnRight = false;
}