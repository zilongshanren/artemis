#ifndef __ENTITY_FACTORY_H__
#define __ENTITY_FACTORY_H__

// artemis
namespace artemis
{
	class Entity;
	class World;
};

// game
#include "SoundFile.h"

class EntityFactory
{
public:
	static artemis::Entity& createExplosion(artemis::World& world, float x, float y);
	static artemis::Entity& createBullet(artemis::World& world, float x, float y, float angle, artemis::Entity& shooter);
	static artemis::Entity& createWall(artemis::World& world, float x, float y);
	static artemis::Entity& createCrate(artemis::World& world, float x, float y, float angleDeg);
	static artemis::Entity& createMammothTank(artemis::World& world, float x, float y);
	static artemis::Entity& createSound(artemis::World& world, const char* soundFileName, SoundType soundType);
};

#endif // __ENTITY_FACTORY_H__