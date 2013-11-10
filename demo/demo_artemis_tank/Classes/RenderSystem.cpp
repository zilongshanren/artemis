#include "RenderSystem.h"

// artemis
#include "include/Entity.h"
#include "include/EntitySystem.h"
#include "include/SystemManager.h"
#include "include/TagManager.h"
#include "include/World.h"

// cocos2dx
USING_NS_CC;

// game
#include "Bullet.h"
#include "CameraSystem.h"
#include "Crate.h"
#include "Constants.h"
#include "Explosion.h"
#include "MammothTank.h"
#include "SpatialForm.h"
#include "Wall.h"

RenderSystem::RenderSystem()
{
	addComponentType<SpatialForm>();
	_spatials = new artemis::Bag<Spatial*>();

	_canvas = Layer::create();
	_canvas->retain();

	_graphics = DrawNode::create();
	_graphics->retain();
}

RenderSystem::~RenderSystem()
{
	_spatials->deleteData();
	delete _spatials;

	_canvas->release();
	_graphics->release();
}

void RenderSystem::onContainerAdded( Container& container )
{
	container.getGraphics()->addChild(_canvas,   (int)Constants::ZOrder::GameEntity);
	container.getGraphics()->addChild(_graphics, (int)Constants::ZOrder::GameEntity);
}

void RenderSystem::onContainerRemoved( Container& container )
{
	container.getGraphics()->removeChild(_canvas);
	container.getGraphics()->removeChild(_graphics);
}

void RenderSystem::initialize()
{
	_spatialFormMapper.init(*world);
	_cameraSystem = (CameraSystem*)world->getSystemManager()->getSystem<CameraSystem>();

	this->setPassive(true);
}

void RenderSystem::begin()
{
	// TODO：cocos2dx如何实现java的渲染模式
	// graphics.scale(cameraSystem->getZoom(), cameraSystem->getZoom());

	_graphics->clear();
}

void RenderSystem::processEntity(artemis::Entity& e)
{
	auto spatial = _spatials->get(e.getId());
	spatial->render(_graphics);
}

void RenderSystem::end()
{
}

void RenderSystem::added(artemis::Entity& e)
{
	auto spatial = this->getSpatial(e);
	if (nullptr != spatial)
	{
		spatial->initalize();
		auto material = spatial->getMaterial();
		if (material)
		{
			_canvas->addChild(material);
		}

		_spatials->set(e.getId(), spatial);
	}
}

void RenderSystem::removed(artemis::Entity& e)
{
	auto spatial  = _spatials->get(e.getId());
	auto material = spatial->getMaterial();
	if (material)
	{
		_canvas->removeChild(material);
	}

	delete spatial;
	_spatials->set(e.getId(), nullptr);
}

Spatial* RenderSystem::getSpatial(artemis::Entity& e)
{
	auto spatialForm = _spatialFormMapper.get(e);
	std::string spatialFormFile = spatialForm->getSpatialFormFile();
	if ("crate" == spatialFormFile)
	{
		return new Crate(world, &e);
	}
	else if ("mammothTank" == spatialFormFile)
	{
		return new MammothTank(world, &e);
	}
	else if ("bullet" == spatialFormFile)
	{
		return new Bullet(world, &e);
	}
	else if ("explosion" == spatialFormFile)
	{
		return new Explosion(world, &e);
	}
	else if ("wall" == spatialFormFile)
	{
		return new Wall(world, &e);
	}

	return nullptr;
}

