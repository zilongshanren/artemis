#include "ArtemisWorld.h"

// artemis
#include "include\ComponentTypeManager.h"
#include "include\EntityManager.h"
#include "include\SystemManager.h"
#include "include\World.h"
using namespace artemis;

// cocos2dx
USING_NS_CC;

// game
#include "Ammo.h"
#include "Constants.h"
#include "Dirty.h"
#include "Health.h"
#include "Physics.h"
#include "ScaleAnimation.h"
#include "SoundFile.h"
#include "SpatialForm.h"
#include "Tower.h"
#include "Transform.h"
#include "TurnFactor.h"
#include "Velocity.h"

artemis::ArtemisWorld::ArtemisWorld()
{
	// 记录各个类的ComponentType到Constant中 
	Constants::ComponentType::AMMO           = ComponentTypeManager::getTypeFor<Ammo>();
	Constants::ComponentType::DIRTY          = ComponentTypeManager::getTypeFor<Dirty>();
	Constants::ComponentType::HEALTH         = ComponentTypeManager::getTypeFor<Health>();
	Constants::ComponentType::PHYSICS        = ComponentTypeManager::getTypeFor<Physics>();
	Constants::ComponentType::SCALEANIMATION = ComponentTypeManager::getTypeFor<ScaleAnimation>();
	Constants::ComponentType::SOUNDFILE      = ComponentTypeManager::getTypeFor<SoundFile>();
	Constants::ComponentType::SPATIALFORM    = ComponentTypeManager::getTypeFor<SpatialForm>();
	Constants::ComponentType::TOWER          = ComponentTypeManager::getTypeFor<Tower>();
	Constants::ComponentType::TRANSFORM      = ComponentTypeManager::getTypeFor<Transform>();
	Constants::ComponentType::TURNFACTOR     = ComponentTypeManager::getTypeFor<TurnFactor>();
	Constants::ComponentType::VELOCITY       = ComponentTypeManager::getTypeFor<Velocity>();
}

artemis::ArtemisWorld::~ArtemisWorld()
{

}

bool artemis::ArtemisWorld::init()
{
	do 
	{
		CC_BREAK_IF(!Component::init());
		this->setName("ArtemisWorld");
		_world.getSystemManager()->initializeAll();
		return true;
	} while (0);
	return false;
}

void artemis::ArtemisWorld::update( float delta )
{
	_world.loopStart();
	_world.setDelta(delta);
	_world.process();
}

EntitySystem* artemis::ArtemisWorld::setSystem( EntitySystem* system )
{
	return _world.getSystemManager()->setSystem(system);
}

artemis::World& artemis::ArtemisWorld::getWorld()
{
	return _world;
}

void artemis::ArtemisWorld::removeAllEntities()
{
	_world.getEntityManager()->removeAllEntities();
}
