#include "CameraSystem.h"

// artemis
#include "include/Entity.h"
#include "include/EntitySystem.h"
#include "include/SystemManager.h"
#include "include/TagManager.h"
#include "include/World.h"

// cocos2dx
#include "cocos2d.h"
USING_NS_CC;

// game 
#include "Constants.h"
#include "Container.h"
#include "DPadLayer.h"

CameraSystem::CameraSystem(Container* container)
	: _dirty(false)
{
	addComponentType<Physics>();
	_graphics = container->getGraphics();
}

CameraSystem::~CameraSystem()
{
	_graphics = nullptr;
}

void CameraSystem::initialize()
{
	CCAssert(_graphics, "graphics should not be nullptr.");

	_physicsMapper.init(*world);

	ensurePlayerEntity();
	
	_zoom = _targetZoom = 1.0f;

	_screenSize = Director::getInstance()->getWinSize();
}

void CameraSystem::processEntities( artemis::ImmutableBag<artemis::Entity*>& bag )
{
	ensurePlayerEntity();
	if (nullptr != _player)
	{
		updatePosition();
		updateZoom();
		fixBoundaries();
		if (_dirty)
		{
			_graphics->setPosition(-getStartX(), -getStartY());
		}		

		// TODO：待实现Input后再补充 
		// input.setOffset(getStartX(), getStartY());
	}
}

bool CameraSystem::checkProcessing()
{
	return true;
}

void CameraSystem::updatePosition()
{
	auto physics = _physicsMapper.get(*_player);
	if (_lookAtX != physics->getX())
	{
		_lookAtX = physics->getX();
		_dirty  = true;
	}

	if (_lookAtY != physics->getY())
	{
		_lookAtY = physics->getY();
		_dirty  = true;
	}
}

void CameraSystem::updateZoom()
{
	if (_targetZoom != _zoom) 
	{
		if (_targetZoom > _zoom) 
		{
			_zoom += 0.0005f * world->getDelta();
			if (_zoom > _targetZoom) 
			{
				_zoom = _targetZoom;
			}
		} 
		else
		{
			_zoom -= 0.0005f * world->getDelta();
			if (_zoom < _targetZoom) 
			{
				_zoom = _targetZoom;
			}
		}

		// TODO：待实现Input后再补充 
		// input.setScale(1f / zoom, 1f / zoom);
	}
}

void CameraSystem::fixBoundaries()
{
	auto stageSize = Constants::UI::stageSize;
	if (getEndX() > stageSize.width)
	{
		_lookAtX -= getEndX() - stageSize.width;
	}
	else if (getStartX() < 0) 
	{
		_lookAtX -= getStartX();
	}

	if (getEndY() > stageSize.height)
	{
		_lookAtY -= getEndY() - stageSize.height;
	}
	else if (getStartY() < 0) 
	{
		_lookAtY -= getStartY();
	}
}

float CameraSystem::getOffsetX() const
{
	return ((1.0f/_zoom) * _screenSize.width)/2.0f;
}

float CameraSystem::getOffsetY() const
{
	return ((1.0f/_zoom) * _screenSize.height)/2.0f;
}

float CameraSystem::getStartX() const
{
	return _lookAtX - getOffsetX();
}

float CameraSystem::getStartY() const
{
	return _lookAtY - getOffsetY();
}

float CameraSystem::getEndX() const
{
	return _lookAtX + getOffsetX();
}

float CameraSystem::getEndY() const
{
	return _lookAtY + getOffsetY();
}

float CameraSystem::getWidth() const
{
	return getEndX() - getStartX();
}

float CameraSystem::getHeight() const
{
	return getEndY() - getStartY();
}

float CameraSystem::getZoom() const
{
	return _zoom;
}

bool CameraSystem::isDirty() const
{
	return _dirty;
}

void CameraSystem::setDirty( bool dirty )
{
	_dirty = dirty;
}
