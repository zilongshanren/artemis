#include "TankzGame.h"
#include "TankzGame.inl"

// artemis
#include "include/Component.h"
#include "include/ComponentMapper.h"
#include "include/Entity.h"
#include "include/EntityProcessingSystem.h"
#include "include/SystemManager.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

// game
#include "AmmoRegenerationSystem.h"
#include "CameraSystem.h"
#include "Constants.h"
#include "DirtySystem.h"
#include "DPadLayer.h"
#include "EntityFactory.h"
#include "HealthSystem.h"
#include "HealthRenderSystem.h"
#include "HudRenderSystem.h"
#include "MovementSystem.h"
#include "PlayerTankMovementSystem.h"
#include "PlayerTankTowerSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "ScaleAnimationSystem.h"
#include "SoundSystem.h"
#include "TerrainRenderSystem.h"

TankzGame::TankzGame()
	: _world(nullptr)
	, _graphics(nullptr)
	, _gui(nullptr)
	, _renderSystem(nullptr)
	, _hudRenderSystem(nullptr)
	, _healthRenderSystem(nullptr)
	, _terrainRenderSystem(nullptr)
	, _cameraSystem(nullptr)
{

}

TankzGame::~TankzGame()
{
	CC_SAFE_RELEASE(_world);
}

cocos2d::Scene* TankzGame::scene()
{
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();

	auto tankzGame = TankzGame::create();
	tankzGame->initArtemisWorld(world);
	tankzGame->initEdgeBox(world);
	tankzGame->initEntities();

	scene->addChild(tankzGame);
	return scene;
}

bool TankzGame::init()
{
	do 
	{
		CC_BREAK_IF(!Layer::init());
		
		_graphics = Layer::create();
		_graphics->setPosition(Point::ZERO);
		this->addChild(_graphics);

		_gui = Layer::create();
		_gui->setPosition(Point::ZERO);
		this->addChild(_gui);

		_input = DPadLayer::create();
		_input->setPosition(Point::ZERO);
		_gui->addChild(_input);

		return true;
	} while (0);
	return false;
}

void TankzGame::initArtemisWorld( cocos2d::PhysicsWorld* world )
{
	_world = new artemis::ArtemisWorld;
	_world->setSystem(new AmmoRegenerationSystem);
	_world->setSystem(_cameraSystem = new CameraSystem(this));
	_world->setSystem(_dirtySystem  = new DirtySystem);
	_world->setSystem(new HealthSystem);
	_world->setSystem(new MovementSystem);
	_world->setSystem(new PhysicsSystem(world));
	_world->setSystem(new PlayerTankMovementSystem(_input));
	_world->setSystem(new PlayerTankTowerSystem(_input));
	_world->setSystem(new ScaleAnimationSystem);
	_world->setSystem(new SoundSystem);
	_world->setSystem(_terrainRenderSystem   = new TerrainRenderSystem(this));
	_world->setSystem(_renderSystem          = new RenderSystem);
	_world->setSystem(_hudRenderSystem       = new HudRenderSystem);
	_world->setSystem(_healthRenderSystem    = new HealthRenderSystem);
	_world->init();

	this->addListener(_hudRenderSystem);
	this->addListener(_healthRenderSystem);
	this->addListener(_renderSystem);
	this->addComponent(_world);
}

void TankzGame::initEntities()
{
	auto designSize = Constants::UI::designSize;
	auto stageSize = Constants::UI::stageSize;

	artemis::World& world = _world->getWorld();
	artemis::Entity& playerTank = EntityFactory::createMammothTank(world, designSize.width*0.5f, designSize.height*0.5f);

	world.getTagManager()->subscribe("PLAYER", playerTank);
	playerTank.refresh();

	EntityFactory::createMammothTank(world, designSize.width, designSize.height).refresh();
	EntityFactory::createMammothTank(world, designSize.width+200.0f, designSize.height*0.3f).refresh();

	EntityFactory::createWall(world, 378.0f, 270.0f).refresh();
	EntityFactory::createWall(world, 378.0f + (5 * 108), 270.0f).refresh();
	EntityFactory::createWall(world, 378.0f + (10 * 108), 270.0f).refresh();

	EntityFactory::createWall(world, 378.0f, 270.0f + (10 * 108)).refresh();
	EntityFactory::createWall(world, 378.0f + (5 * 108), 270.0f + (10 * 108)).refresh();
	EntityFactory::createWall(world, 378.0f + (10 * 108), 270.0f + (10 * 108)).refresh();

	srand(time(0));
	for (int i = 0; 20 > i; i++) 
	{
		int x = rand()%int(stageSize.width);
		int y = rand()%int(stageSize.height);
		int g  = rand()%3;

		for (int a = 0; g > a; a++) 
		{
			EntityFactory::createCrate(world, x + rand()%100, y + rand()%100, rand()%360).refresh();
		}
	}
}

void TankzGame::onEnter()
{
	Container::onEnter();

	this->scheduleUpdate();
	this->setKeyboardEnabled(true);
}

void TankzGame::onExit()
{
	Container::onExit();
	
	this->unscheduleUpdate();
	this->setKeyboardEnabled(false);
}

void TankzGame::onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
	_world->removeAllEntities();
	SimpleAudioEngine::getInstance()->end();
	Director::getInstance()->end();
}

void TankzGame::update( float delta )
{
//	float x, y,z;
//	_graphics->getCamera()->getEye(&x, &y, &z);
//	_graphics->getCamera()->setEye(x, y, ++z);

	Container::update(delta);

	_terrainRenderSystem->process();
	_renderSystem->process();
	_hudRenderSystem->process();
	_healthRenderSystem->process();

	// TODO：思考如何移除cameraSystem的dirty机制 
	_cameraSystem->setDirty(false);

	_dirtySystem->process();
}



void TankzGame::initEdgeBox( cocos2d::PhysicsWorld* world )
{
	auto stageSize = Constants::UI::stageSize;
	auto b = PhysicsBody::createEdgeBox(stageSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 11.0f);
	b->setPosition(Point(stageSize.width*0.5f, stageSize.height*0.5f));
	b->setCategoryBitmask(Constants::CategoryBitmask::WORLD);
	b->setContactTestBitmask(Constants::CategoryBitmask::BULLET);
	world->addBody(b);
}
