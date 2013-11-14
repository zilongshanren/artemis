#ifndef __SPATIAL_H__
#define __SPATIAL_H__

// cocos2dx
#include "CCNode.h"
#include "CCDrawNode.h"

namespace artemis
{
	class Entity;
	class World;
};

class Spatial 
{
public:
	Spatial(artemis::World* world, artemis::Entity* owner): world(world), owner(owner) {}
	virtual ~Spatial() {}

	virtual void initalize() = 0;
	virtual void render(cocos2d::DrawNode* graphics) = 0;
	virtual cocos2d::Node* getMaterial() const = 0;

protected:
	artemis::World* world;
	artemis::Entity* owner;
};

#endif // __SPATIAL_H__