#include "Explosion.h"

// artemis
#include "Component.h"
#include "Entity.h"
#include "World.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game
#include "Constants.h"

Explosion::Explosion( artemis::World* world, artemis::Entity* owner )
	: Spatial(world, owner)
	, _transform(nullptr)
{
}

Explosion::~Explosion()
{
}

void Explosion::initalize()
{
	_transform      = (Transform*)owner->getComponent(Constants::ComponentType::TRANSFORM);
	_scaleAnimation = (ScaleAnimation*)owner->getComponent(Constants::ComponentType::SCALEANIMATION);
}

void Explosion::render(DrawNode* graphics)
{
	auto radius = RADIUS*_scaleAnimation->getScale();

	Point pos(_transform->getX(), _transform->getY());
	graphics->drawCircle(pos, radius, radius, COLOR);
}

cocos2d::Node* Explosion::getMaterial() const
{
	return nullptr;
}

const float Explosion::RADIUS = 128.0f;
const Color4F Explosion::COLOR = Color4F(1.0f, 216.0f/255.0f, 0.5f, 1.0f);