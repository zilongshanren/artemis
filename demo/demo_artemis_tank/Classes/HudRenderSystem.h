#ifndef __HUD_RENDER_SYSTEM_H__
#define __HUD_RENDER_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "Entity.h"
#include "EntitySystem.h"

// cocos2dx
#include "ccTypes.h"
NS_CC_BEGIN
class LabelBMFont;
class Layer;
class Node;
NS_CC_END

// game
#include "Ammo.h"
#include "Container.h"
#include "Health.h"
#include "Physics.h"
#include "PlayerEntitySystem.h"
class CameraSystem;
class MiniMap;
class StatusBar;

class HudRenderSystem 
	: public PlayerEntitySystem
	, public ContainerListener
{
public:
	HudRenderSystem();
	~HudRenderSystem();

public: // artemis
	virtual void initialize() override;
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) override;
	virtual bool checkProcessing() override;

public: // container
	virtual void onContainerAdded(Container& container) override;
	virtual void onContainerRemoved(Container& container) override;

public:
	void renderMinimap();
	void renderHealth();
	void renderAmmo();
	 
private:
	StatusBar*       _ammoBar;
	cocos2d::Layer*  _canvas;
	StatusBar*       _healthBar;
	MiniMap*         _miniMap;

	CameraSystem*    _cameraSystem;

	artemis::ComponentMapper<Ammo>    _ammoMapper;
	artemis::ComponentMapper<Health>  _healthMapper;
	artemis::ComponentMapper<Physics> _physicsMapper;
};

#endif // __HUD_RENDER_SYSTEM_H__