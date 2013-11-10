#include "Crate.h"

// artemis
#include "include\ComponentTypeManager.h"
#include "include\Entity.h"

// game
#include "Constants.h"
#include "Physics.h"
#include "sprite_nodes\CCSprite.h"

Crate::Crate( artemis::World* world, artemis::Entity* owner )
	: Spatial(world, owner)
	, _physics(nullptr)
{
}

Crate::~Crate()
{
	CC_SAFE_RELEASE(_material);
}

void Crate::initalize()
{
	_physics = (Physics*)owner->getComponent(Constants::ComponentType::PHYSICS);

	_material = cocos2d::Sprite::create("crate.png");
	_material->setColor(cocos2d::Color3B(51.0f, 204.0f, 69.0f));
	_material->retain();
}

void Crate::render(cocos2d::DrawNode* graphics)
{
	_material->setRotation(_physics->getRotation());
	_material->setPosition(cocos2d::Point(_physics->getX(), _physics->getY()));
}

cocos2d::Node* Crate::getMaterial() const
{
	return _material;
}