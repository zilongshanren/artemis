#include "HudRenderSystem.h"

// artemis
#include "include/Entity.h"
#include "include/EntitySystem.h"
#include "include/SystemManager.h"
#include "include/TagManager.h"
#include "include/World.h"

// cocos2dx
#include "ccTypes.h"
#include "draw_nodes/CCDrawNode.h"
#include "label_nodes/CCLabelBMFont.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "sprite_nodes/CCSprite.h"
USING_NS_CC;

// game
#include "CameraSystem.h"
#include "Constants.h"
#include "MiniMap.h"
#include "StatusBar.h"

HudRenderSystem::HudRenderSystem()
	: _healthBar(nullptr)
	, _ammoBar(nullptr)
	, _miniMap(nullptr)
	, _cameraSystem(nullptr)
{
	_canvas = Layer::create();
	_canvas->retain();

	addComponentType<Ammo>();
	addComponentType<Health>();
	addComponentType<Physics>();
}

HudRenderSystem::~HudRenderSystem()
{
	CC_SAFE_RELEASE(_canvas);
}

void HudRenderSystem::initialize()
{
	_ammoMapper.init(*world);
	_healthMapper.init(*world);
	_physicsMapper.init(*world);

	_cameraSystem   = (CameraSystem*)world->getSystemManager()->getSystem<CameraSystem>();

	auto designSize = Constants::UI::designSize;

	// health能量槽
	_healthBar = StatusBar::create("Health", 100.0f);
	_healthBar->setPosition(Point(9.0f, designSize.height-60.0f));
	_canvas->addChild(_healthBar);

	// ammo能量槽
	_ammoBar = StatusBar::create("Ammo", 30.0f);
	_ammoBar->setPosition(Point(9.0f, designSize.height-120.0f));
	_canvas->addChild(_ammoBar);

	// 小地图
	_miniMap = MiniMap::create();
	_miniMap->setPosition(Point(designSize.width-10.0f, designSize.height-10.0f));
	_miniMap->setAnchorPoint(Point(1.0f, 1.0f));
	_canvas->addChild(_miniMap);
	
	// artemis 相关初始化 
	this->ensurePlayerEntity();
	this->setPassive(true);
}

void HudRenderSystem::processEntities(artemis::ImmutableBag<artemis::Entity*>& bag)
{
	this->ensurePlayerEntity();

	if (nullptr != _player ) 
	{
		this->renderHealth();
		this->renderAmmo();
		this->renderMinimap();
	}
}

bool HudRenderSystem::checkProcessing()
{
	return true;
}

void HudRenderSystem::renderMinimap()
{
	auto entities = world->getGroupManager()->getEntities(Constants::Groups::CRATE);
	auto tanks = world->getGroupManager()->getEntities(Constants::Groups::TANK);
	_miniMap->render(_cameraSystem, entities, tanks, _physicsMapper);
}

void HudRenderSystem::renderHealth()
{
	static float s_percent = -1.0f;
	auto health = _healthMapper.get(*_player);
	auto percent = health->getHealthStatus();
	if (s_percent != percent)
	{
		_healthBar->setPercent(percent);
		s_percent = percent;
	}
}

void HudRenderSystem::renderAmmo()
{
	static float s_percent = -1.0f;
	auto ammo = _ammoMapper.get(*_player);
	auto percent = ammo->getAmmoStatus();
	if (s_percent != percent)
	{
		_ammoBar->setPercent(percent);
		s_percent = percent;
	}
}

void HudRenderSystem::onContainerAdded( Container& container )
{
	container.getGUI()->addChild(_canvas, (int)Constants::ZOrder::HubRenderSystem);
}

void HudRenderSystem::onContainerRemoved( Container& container )
{
	container.getGUI()->removeChild(_canvas);
}
