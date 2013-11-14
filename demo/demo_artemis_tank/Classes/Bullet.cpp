#include "Bullet.h"

// artemis
#include "ComponentTypeManager.h"
#include "Entity.h"

// game
#include "Constants.h"
#include "Physics.h"

Bullet::Bullet( artemis::World* world, artemis::Entity* owner )
	: Spatial(world, owner)
	, _physics(nullptr)
{
}

Bullet::~Bullet()
{
	CC_SAFE_RELEASE(_material);
}


void Bullet::initalize()
{
	_physics = (Physics*)owner->getComponent(Constants::ComponentType::PHYSICS);

	_material = cocos2d::Sprite::create("bullet.png");
	_material->setColor(cocos2d::Color3B(51.0f, 204.0f, 69.0f));
	_material->retain();
}

void Bullet::render(cocos2d::DrawNode* graphics)
{
	_material->setRotation(_physics->getRotation());
	_material->setPosition(cocos2d::Point(_physics->getX(), _physics->getY()));
}

cocos2d::Node* Bullet::getMaterial() const
{
	return _material;
}

