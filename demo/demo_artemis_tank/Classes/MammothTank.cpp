#include "MammothTank.h"

// artemis
#include "Component.h"
#include "Entity.h"
#include "World.h"

// cocos2dx
USING_NS_CC;

// game
#include "Constants.h"
#include "Physics.h"
#include "Tankz.h"
#include "Tower.h"
#include "TurnFactor.h"
#include "Utils.h"
#include "Velocity.h"

MammothTank::MammothTank( artemis::World* world, artemis::Entity* owner )
	: Spatial(world, owner)
	, _material(nullptr)
	, _physics(nullptr)
	, _tower(nullptr)
	, _turnFactor(nullptr)
	, _velocity(nullptr)
{
}

MammothTank::~MammothTank()
{
	CC_SAFE_RELEASE(_material);
}

void MammothTank::initalize()
{
	_physics    = (Physics*)owner->getComponent(Constants::ComponentType::PHYSICS);
	_tower      = (Tower*)owner->getComponent(Constants::ComponentType::TOWER);
	_turnFactor = (TurnFactor*)owner->getComponent(Constants::ComponentType::TURNFACTOR);
	_velocity   = (Velocity*)owner->getComponent(Constants::ComponentType::VELOCITY);

	_material = Tankz::create();
	_material->retain();
}

void MammothTank::render(cocos2d::DrawNode* graphics)
{
	_material->setPositionX(_physics->getX());
	_material->setPositionY(_physics->getY());

	_material->setRotation(-_physics->getRotation());
	_material->getTower()->setRotation(-_tower->getRotation());

	auto angle = _turnFactor->getFactor()*360.0f;
	angle = MIN(angle, 45.0f);
	angle = MAX(angle, -45.0f);
	_material->getFrontTrackL()->setRotation(angle);
	_material->getFrontTrackR()->setRotation(angle);
}

cocos2d::Node* MammothTank::getMaterial() const
{
	return _material;
}
