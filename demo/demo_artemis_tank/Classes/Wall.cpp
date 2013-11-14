#include "Wall.h"

// artemis
#include "ComponentTypeManager.h"
#include "Entity.h"

// game
#include "Constants.h"
#include "Physics.h"

Wall::Wall( artemis::World* world, artemis::Entity* owner )
	: Spatial(world, owner)
	, _physics(nullptr)
{
}

Wall::~Wall()
{
	CC_SAFE_RELEASE(_material);
}

void Wall::initalize()
{
	_physics = (Physics*)owner->getComponent(Constants::ComponentType::PHYSICS);
	
	_material = cocos2d::Sprite::create("wall.png");
	_material->retain();
}

void Wall::render(cocos2d::DrawNode* graphics)
{
	_material->setRotation(_physics->getRotation());
	_material->setPosition(cocos2d::Point(_physics->getX(), _physics->getY()));
}

cocos2d::Node* Wall::getMaterial() const 
{
	return _material;
}

