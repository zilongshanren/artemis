#include "EntityFactory.h"

// C++
#include <stdlib.h>

// artemis
#include "World.h"
#include "Entity.h"

// game
#include "Ammo.h"
#include "Constants.h"
#include "Dirty.h"
#include "Health.h"
#include "Physics.h"
#include "ScaleAnimation.h"
#include "SpatialForm.h"
#include "Tower.h"
#include "Transform.h"
#include "TrigLUT.h"
#include "TurnFactor.h"
#include "Velocity.h"

using namespace artemis;
using namespace Constants;
USING_NS_CC;

Entity& EntityFactory::createExplosion( World& world, float x, float y )
{
	Entity& e = world.createEntity();

	auto scaleAnimation = new ScaleAnimation;
	scaleAnimation->setActive(true);
	scaleAnimation->setMinScale(1.0f/100.0f);
	scaleAnimation->setSpeed(-4.0f);
	e.addComponent(scaleAnimation);
	e.addComponent(new SpatialForm("explosion"));
	e.addComponent(new Transform(x, y));
	return e;
}

Entity& EntityFactory::createBullet( World& world, float x, float y, float angle, Entity& shooter )
{
	Entity& e = world.createEntity();
	world.getGroupManager()->set(Groups::BULLET, e);

	e.addComponent(new SpatialForm("bullet"));
	e.addComponent(new Transform(x, y, angle));

	PhysicsMaterial material(PHYSICS_INFINITY, 0.0f, 10.0f);
	auto b = PhysicsBody::createBox(Size(10.0f, 10.0f));
	b->setMass(0.2f);
	b->setUserData(&e);
	b->setRotation(CC_DEGREES_TO_RADIANS(angle));
	b->setAngularDamping(0.002f);
	b->setPosition(Point(x, y));
	b->setCategoryBitmask(CategoryBitmask::BULLET);
	b->setContactTestBitmask(CategoryBitmask::ALL);
	b->setVelocity(Point(1000.0f*TrigLUT::cosDeg(angle), 1000.0f*TrigLUT::sinDeg(angle)));
	
	e.addComponent(new Physics(b));

	return e;
}

Entity& EntityFactory::createWall( World& world, float x, float y )
{
	Entity& e = world.createEntity();
	world.getGroupManager()->set(Groups::WALL, e);

	e.addComponent(new SpatialForm("wall"));

	// 设置最大摩擦力为10000，防止Wall移动 
	// b->setDynamic(false);后Wall是不会动了，但也不会发生碰撞，坑爹... 
	PhysicsMaterial material(PHYSICS_INFINITY, 0.0f, 10000.0f); 
	auto b = PhysicsBody::createBox(Size(214.0f, 214.0f), material);
	b->setUserData(&e);
	b->setDynamic(true);
	b->setAngularDamping(0.1f);
	b->setLinearDamping(10.0f);
	b->setRotationEnable(false);
	b->setPosition(Point(x, y));
	b->setCategoryBitmask(CategoryBitmask::WALL);
	b->setContactTestBitmask(CategoryBitmask::BULLET);
	e.addComponent(new Physics(b));
	
	return e;
}

Entity& EntityFactory::createCrate( World& world, float x, float y, float angleDeg )
{
	Entity& e = world.createEntity();
	world.getGroupManager()->set(Groups::CRATE, e);

	e.addComponent(new Dirty);
	e.addComponent(new Health(100.0f, 160.0f));
	e.addComponent(new SpatialForm("crate"));

	PhysicsMaterial material(PHYSICS_INFINITY, 0.0f, 200.0f);
	auto b = PhysicsBody::createBox(Size(50.0f, 50.0f), material);
	b->setMass(1.0f);
	b->setUserData(&e);
	b->setRotation(angleDeg);
	b->setAngularDamping(0.1f);
	b->setLinearDamping(10.0f);
	b->setPosition(Point(x, y));
	b->setMoment(PHYSICS_INFINITY);
	b->setCategoryBitmask(CategoryBitmask::CRATE);
	b->setContactTestBitmask(CategoryBitmask::ALL);
	e.addComponent(new Physics(b));

	return e;
}

Entity& EntityFactory::createMammothTank( World& world, float x, float y )
{
	Entity& e = world.createEntity();
	world.getGroupManager()->set(Groups::TANK, e);

	e.addComponent(new Ammo(1000.0f, 1000.0f));
	e.addComponent(new Dirty);
	e.addComponent(new Health(110.0f, 180.0f));
	e.addComponent(new SpatialForm("mammothTank"));
	e.addComponent(new TurnFactor);
	e.addComponent(new Tower);
	e.addComponent(new Velocity);

	PhysicsMaterial material(PHYSICS_INFINITY, 0.0f, 100.0f);
	auto b = PhysicsBody::createBox(Size(125.0f, 104.0f), material);
	b->setMass(1.0f);
	b->setUserData(&e);
	b->setAngularDamping(0.1f);
	b->setLinearDamping(10.0f);
	b->setPosition(Point(x, y));
	b->setCategoryBitmask(CategoryBitmask::TANK);
	b->setContactTestBitmask(CategoryBitmask::ALL);
 	e.addComponent(new Physics(b));

	return e;
}

Entity& EntityFactory::createSound( World& world, const char* soundFileName, SoundType soundType )
{
	Entity& sound = world.createEntity();
	sound.addComponent(new SoundFile(soundFileName, soundType));
	return sound;
}
