#ifndef __TANKZ_GAME_H__
#define __TANKZ_GAME_H__

// artemis
#include "ArtemisWorld.h"

// cocos2dx
#include "layers_scenes_transitions_nodes\CCLayer.h"
NS_CC_BEGIN
class Scene;
class PhysicsWorld;
NS_CC_END

// game
#include "Container.h"
class CameraSystem;
class DirtySystem;
class RenderSystem;
class HudRenderSystem;
class HealthRenderSystem;
class TerrainRenderSystem;

class TankzGame : public Container
{
public:
	TankzGame();
	virtual ~TankzGame();

public: // cocos2dx
	static cocos2d::Scene* scene();
	CREATE_FUNC(TankzGame);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override { }
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void update(float delta) override;

public: // container
	virtual DPadLayer* getInput() const override;
	virtual cocos2d::Node* getGraphics() const override;
	virtual cocos2d::Node* getGUI() const override;

public:
	void initArtemisWorld(cocos2d::PhysicsWorld* world);
	void initEdgeBox( cocos2d::PhysicsWorld* world );
	void initEntities();

private:
	DPadLayer*             _input;
	cocos2d::Node*		   _graphics;
	cocos2d::Node*         _gui;

	artemis::ArtemisWorld* _world;
	CameraSystem*          _cameraSystem;
	DirtySystem*           _dirtySystem;
	RenderSystem*          _renderSystem;
	HudRenderSystem*       _hudRenderSystem;
	HealthRenderSystem*    _healthRenderSystem;
	TerrainRenderSystem*   _terrainRenderSystem;
};

#endif // __TANKZ_GAME_H__