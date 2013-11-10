#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\DelayedEntitySystem.h"

// cocos2dx
#include "physics\CCPhysicsContact.h"
NS_CC_BEGIN
class Scene;
class PhysicsWorld;
NS_CC_END

// game
#include "Physics.h"
#include "Transform.h"

class PhysicsSystem : public artemis::DelayedEntitySystem, public cocos2d::PhysicsContactListener
{
public:
	PhysicsSystem(cocos2d::PhysicsWorld* world);
	~PhysicsSystem();

public: // artemis
	virtual void initialize() override;

protected: // artemis
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag, float accumulatedDelta) override;
	virtual bool checkProcessing() override;
	virtual void added(artemis::Entity& e) override;
	virtual void removed(artemis::Entity& e) override;

public:

private:
	void handleBulletHittingTarget(artemis::Entity& bullet, artemis::Entity& target);
	void removeBullet(artemis::Entity& bullet);
	void addDamageToTarget(artemis::Entity& crate);
	void initPhysicsListener();

private:
	cocos2d::PhysicsWorld* _physicsWorld;

	artemis::ComponentMapper<Physics> _physicsMapper;
};


#endif // __PHYSICS_SYSTEM_H__