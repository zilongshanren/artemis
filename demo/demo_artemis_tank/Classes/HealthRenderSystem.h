#ifndef __HEALTH_RENDER_SYSTEM_H__
#define __HEALTH_RENDER_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntityProcessingSystem.h"

// cocos2dx
#include "cocos2d.h"
NS_CC_BEGIN
class Dictionary;
NS_CC_END

// game
#include "Container.h"
#include "Dirty.h"
#include "Health.h"
#include "Physics.h"
class CameraSystem;

class HealthRenderSystem 
	: public artemis::EntityProcessingSystem
	, public ContainerListener
{
public:
	HealthRenderSystem();
	~HealthRenderSystem();

public: // artemis
	virtual void initialize() override;
	virtual void begin() override;
	virtual void processEntity(artemis::Entity& e) override;
	virtual void end() override;

	virtual void removed(artemis::Entity &e) override;
	virtual void added(artemis::Entity &e) override;

public: // container
	virtual void onContainerAdded(Container& container) override;
	virtual void onContainerRemoved(Container& container) override;

private:
	cocos2d::Dictionary* _barDictionary;
	CameraSystem*        _cameraSystem;
	cocos2d::Layer*      _canvas;

	artemis::ComponentMapper<Dirty>       _dirtyMapper;
	artemis::ComponentMapper<Health>      _healthMapper;
	artemis::ComponentMapper<Physics>     _physicsMapper;
};

#endif // __HEALTH_RENDER_SYSTEM_H__