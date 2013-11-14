#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntityProcessingSystem.h"

// cococ2dx
#include "cocos2d.h"

// game
#include "CameraSystem.h"
#include "Container.h"
#include "Spatial.h"
#include "SpatialForm.h"

class RenderSystem 
	: public artemis::EntityProcessingSystem
	, public ContainerListener
{
public:
	RenderSystem();
	~RenderSystem();

public: // artemis
	virtual void initialize() override;
	virtual void begin() override;
	virtual void processEntity(artemis::Entity& e) override;
	virtual void end() override;
	virtual void added(artemis::Entity& e) override;
	virtual void removed(artemis::Entity& e) override;

public: // container
	virtual void onContainerAdded(Container& container) override;
	virtual void onContainerRemoved(Container& container) override;

private:
	Spatial* getSpatial(artemis::Entity& e);

private:
	CameraSystem*           _cameraSystem;
	cocos2d::Layer*         _canvas;
	cocos2d::DrawNode*      _graphics;
	artemis::Bag<Spatial*>* _spatials;

	artemis::ComponentMapper<SpatialForm> _spatialFormMapper;
};

#endif // __RENDER_SYSTEM_H__