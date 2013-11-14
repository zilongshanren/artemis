#include "PhysicsSystem.h"

// artemis
#include "Entity.h"
using namespace artemis;

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game
#include "Constants.h"
#include "Dirty.h"
#include "EntityFactory.h"
#include "Health.h"
using namespace Constants;

PhysicsSystem::PhysicsSystem(PhysicsWorld* world)
	: _physicsWorld(nullptr)
{
	CCAssert(world, "physicsWorld should not be nullptr.");
	_physicsWorld = world;

	addComponentType<Physics>();
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::initialize()
{
	_physicsMapper.init(*world);

	_physicsWorld->setGravity(Point::ZERO);
	_physicsWorld->registerContactListener(this);

	initPhysicsListener();
}


void PhysicsSystem::processEntities( ImmutableBag<Entity*>& bag, float accumulatedDelta )
{
	// do nothing. 
}

bool PhysicsSystem::checkProcessing()
{
	// 用于更新物理引擎的world，由于CCScene已经做了，所以这里可以忽略更新
	return false; 
}

void PhysicsSystem::added( Entity& e )
{
	auto collidable = (Physics*)e.getComponent(Constants::ComponentType::PHYSICS);
	auto body = collidable->getBody();
	body->setUserData(&e);

	_physicsWorld->addBody(body);
}

void PhysicsSystem::removed( Entity& e )
{
	auto physic = (Physics*)e.getComponent(Constants::ComponentType::PHYSICS);
	auto body = physic->getBody();
	body->setUserData(nullptr);

	_physicsWorld->removeBody(body);
}

void PhysicsSystem::handleBulletHittingTarget( Entity& bullet, Entity& target )
{
	addDamageToTarget(target);
	removeBullet(bullet);
}

void PhysicsSystem::addDamageToTarget( Entity& crate )
{
	auto dirty  = (Dirty*) crate.getComponent(Constants::ComponentType::DIRTY);
	auto health = (Health*)crate.getComponent(Constants::ComponentType::HEALTH);
	if (health && dirty)
	{
		health->addDamage(10.0f);
		dirty->setDirty(true);
	}
}

void PhysicsSystem::removeBullet( artemis::Entity& bullet )
{
	auto bp = (Physics*)bullet.getComponent(Constants::ComponentType::PHYSICS);
	EntityFactory::createExplosion(*world, bp->getX(), bp->getY()).refresh();
	world->deleteEntity(bullet);
}

void PhysicsSystem::initPhysicsListener()
{
	onContactBegin = [this](PhysicsWorld& world, const PhysicsContact& contact)	
	{
		return true; 
	};

	onContactPreSolve = [this](PhysicsWorld& world, const PhysicsContact& contact, const PhysicsContactPreSolve& solve)
	{
		return true;
	};
	onContactPostSolve = [this](PhysicsWorld& world, const PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};

	onContactEnd = [this](PhysicsWorld& world, const PhysicsContact& contact)
	{
		auto shapeA = contact.getShapeA();
		auto shapeB = contact.getShapeB();
		auto bodyA  = shapeA->getBody();
		auto bodyB  = shapeB->getBody();

		auto entityA = (Entity*)bodyA->getUserData();
		auto entityB = (Entity*)bodyB->getUserData();
		if (nullptr == entityA || nullptr == entityB)
		{
			return;
		}

		auto categoryA = bodyA->getCategoryBitmask();
		auto categoryB = bodyB->getCategoryBitmask();

		if(((categoryA & CategoryBitmask::CRATE)  != 0) &&
		   ((categoryB & CategoryBitmask::BULLET) != 0))
		{
			handleBulletHittingTarget(*entityB, *entityA);
		}
		else if(((categoryB & CategoryBitmask::CRATE)  != 0) &&
			    ((categoryA & CategoryBitmask::BULLET) != 0))
		{
			handleBulletHittingTarget(*entityA, *entityB);
		}
		else if(((categoryB & CategoryBitmask::TANK)   != 0) && 
			    ((categoryA & CategoryBitmask::BULLET) != 0))
		{
			handleBulletHittingTarget(*entityA, *entityB);
		}
		else if(((categoryB & CategoryBitmask::BULLET) != 0) &&
			    ((categoryA & CategoryBitmask::TANK)   != 0))
		{
			handleBulletHittingTarget(*entityB, *entityA);
		}
		else if(((categoryB & CategoryBitmask::BULLET) != 0) &&
			    ((categoryA & CategoryBitmask::WALL)   != 0)) 
		{
			handleBulletHittingTarget(*entityB, *entityA);
		}
		else if(((categoryB & CategoryBitmask::WALL)   != 0) && 
			    ((categoryA & CategoryBitmask::BULLET) != 0))
		{
			handleBulletHittingTarget(*entityA, *entityB);
		}
		else if(((categoryB & CategoryBitmask::BULLET) != 0) && 
			    ((categoryA & CategoryBitmask::BULLET) != 0))
		{
			removeBullet(*entityB);
			removeBullet(*entityA);
		}
		else if(((categoryB & CategoryBitmask::BULLET) != 0) && 
			   ((categoryA & CategoryBitmask::WORLD)   != 0))
		{
			bodyB->setVelocity(Point::ZERO);
			removeBullet(*entityB);
		}
		else if(((categoryB & CategoryBitmask::WORLD) != 0) && 
			   ((categoryA & CategoryBitmask::BULLET) != 0))
		{
			bodyA->setVelocity(Point::ZERO);
			removeBullet(*entityA);
		}
	};
}