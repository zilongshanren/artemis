#ifndef __TERRAIN_RENDER_SYSTEM_H__
#define __TERRAIN_RENDER_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\EntitySystem.h"

// cocos2dx
#include "tilemap_parallax_nodes\CCTMXTiledMap.h"

// game
class CameraSystem;
class Container;

class TerrainRenderSystem : public artemis::EntitySystem
{
public:
	TerrainRenderSystem(Container* container);

public:
	virtual void initialize() override;
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) override;
	virtual bool checkProcessing() override;

private:
	CameraSystem* _cameraSystem;
	Container* _container;
	cocos2d::TMXTiledMap* _map;
};


#endif // __TERRAIN_RENDER_SYSTEM_H__