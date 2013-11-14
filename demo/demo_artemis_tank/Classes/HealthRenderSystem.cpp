#include "HealthRenderSystem.h"

// artemis
#include "Entity.h"
#include "World.h"
#include "SystemManager.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game
#include "CameraSystem.h"
#include "Constants.h"
#include "GradientColorUtil.h"

HealthRenderSystem::HealthRenderSystem()
	: _barDictionary(nullptr)
	, _cameraSystem(nullptr)
	, _canvas(nullptr)
{
	addComponentType<Dirty>();
	addComponentType<Health>();
	addComponentType<Physics>();
}

HealthRenderSystem::~HealthRenderSystem()
{
	CC_SAFE_RELEASE(_barDictionary);
	CC_SAFE_RELEASE(_canvas);
}

void HealthRenderSystem::initialize() 
{
	_dirtyMapper.init(*world);
	_healthMapper.init(*world);
	_physicsMapper.init(*world);

	_cameraSystem = (CameraSystem*)world->getSystemManager()->getSystem<CameraSystem>();

	_canvas = Layer::create();
	_canvas->setPosition(Point::ZERO);
	_canvas->retain();

	_barDictionary = Dictionary::create();
	_barDictionary->retain();

	this->setPassive(true);
}

void HealthRenderSystem::onContainerAdded( Container& container )
{
	container.getGraphics()->addChild(_canvas, (int)Constants::ZOrder::HealthRenderSystem);
}

void HealthRenderSystem::onContainerRemoved( Container& container )
{
	container.getGraphics()->removeChild(_canvas);
}

void HealthRenderSystem::begin()
{
	// TODO：cocos2dx如何实现java的渲染模式
	// g.scale(cameraSystem->getZoom(), cameraSystem->getZoom());
}

void HealthRenderSystem::processEntity(artemis::Entity& e)
{
	auto dirty   = _dirtyMapper.get(e);
	auto health  = _healthMapper.get(e);
	auto physics = _physicsMapper.get(e);
	auto bodybox = (PhysicsShapeBox*)physics->getBody()->getShape();

	Point pos;
	pos.x = physics->getX();
	pos.y = physics->getY() - bodybox->getSize().height*0.6f;

	auto node = (Node*)_barDictionary->objectForKey(e.getId());
	if (node)
	{
		if (dirty->isDirty())
		{
			auto hpBar = (ProgressTimer*)node->getChildByTag(1);
			hpBar->setPercentage(health->getHealthStatus());
			hpBar->setColor(GradientColorUtil::getGradientColor(health->getHealthStatus()));
		}
		node->setPosition(pos);
	}
}

void HealthRenderSystem::end()
{
}

void HealthRenderSystem::added( artemis::Entity &e )
{
	auto bg = Sprite::create("bar.png");
	bg->setColor(Color3B(64, 64, 64));
	bg->setOpacity(160);
	bg->setTag(e.getId());

	auto hpBar = ProgressTimer::create(Sprite::create("bar.png"));
	hpBar->setColor(Color3B::GREEN);
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point::ZERO);
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setAnchorPoint(Point::ZERO);
	hpBar->setPosition(Point::ZERO);
	bg->addChild(hpBar, 1, 1);

	_canvas->addChild(bg);
	_barDictionary->setObject(bg, e.getId());

	auto dirty = (Dirty*)e.getComponent(Constants::ComponentType::DIRTY);
	dirty->setDirty(true);
}

void HealthRenderSystem::removed( artemis::Entity &e )
{
	_canvas->removeChildByTag(e.getId());
	_barDictionary->removeObjectForKey(e.getId());
}
