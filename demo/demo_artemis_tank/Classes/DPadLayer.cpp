#include "DPadLayer.h"

// C++
#include <algorithm>
#include <stdlib.h>

// cocos2dx
#include "menu_nodes\CCMenuItem.h"
#include "sprite_nodes\CCSprite.h"
#include "textures\CCTexture2D.h"
#include "textures\CCTextureCache.h"
USING_NS_CC;

// game
#include "Constants.h"
#include "JoyStick.h"
#include "PadButtonGroup.h"
using namespace Constants;


DPadLayer::DPadLayer()
	: _mouse(Point::ZERO)
	, _tankJoystick(nullptr)
	, _towerJoystick(nullptr)
	, _preKeyCode(DPadKeyCode::NONE)
{
}

DPadLayer::~DPadLayer()
{

}

bool DPadLayer::init()
{
	do 
	{
		CC_BREAK_IF(!Layer::init());
		auto designSize = UI::designSize;
		auto textureCache = TextureCache::getInstance();
		_tankJoystick = JoyStick::create(23.0f, 64.0f, false, true, false, true);
		_tankJoystick->setPosition(Point(64.0f, 164.0f));
		_tankJoystick->setBallTexture("joystick/ball.png");
		_tankJoystick->setStickTexture("joystick/stick.png");
		_tankJoystick->setDockTexture("joystick/dock.png");
		_tankJoystick->addListener(this);
		this->addChild(_tankJoystick);

		_towerJoystick = JoyStick::create(23.0f, 64.0f, false, true, false, true);
		_towerJoystick->setPosition(Point(designSize.width-64.0f, 164.0f));
		_towerJoystick->setHitAreaWithRect(Rect(designSize.width*0.5f, 0.0f, designSize.width*0.5f, designSize.height*0.5f));
		_towerJoystick->setBallTexture("joystick/ball.png");
		_towerJoystick->setStickTexture("joystick/stick.png");
		_towerJoystick->setDockTexture("joystick/dock.png");
		_towerJoystick->addListener(this);
		this->addChild(_towerJoystick);

		return true;
	} while (0);
	return false;
}

void DPadLayer::onJoyStickUpdate( cocos2d::Node* sender, float angle, cocos2d::Point direction, float power )
{
	if (sender == _tankJoystick)
	{	
		_mouse.x += direction.x*10;
		_mouse.y += direction.y*10;

		auto directId = _getDirectionID(direction, 0.5f, 0.3f);

		if (directId != _preKeyCode)
		{
			if (_curKeyCodeList.size() < 5)
			{
				_curKeyCodeList.push_back(directId);
			}
			else
			{
				_curKeyCodeList.erase(_curKeyCodeList.begin());
				_curKeyCodeList.push_back(directId);
			}

			_preKeyCode = directId;
		}

		for (auto listener : _listenerList)
		{
			listener->onTankJoyStickUpdate(this, angle, direction, power);
		}
	}
	else if (sender == _towerJoystick)
	{
		for (auto listener : _listenerList)
		{
			listener->onTowerJoyStickUpdate(this, angle, direction, power);
		}
	}
}

void DPadLayer::onJoyStickActivated( cocos2d::Node* sender )
{
	if (sender == _tankJoystick)
	{	
		for (auto listener : _listenerList)
		{	
			listener->onTankJoyStickActivated(this);
		}
	}
	else if (sender == _towerJoystick)
	{
		for (auto listener : _listenerList)
		{	
			listener->onTowerJoyStickActivated(this);
		}
	}	

	_curKeyCodeList.clear();
}

void DPadLayer::onJoyStickDeactivated( cocos2d::Node* sender )
{
	if (sender == _tankJoystick)
	{	
		for (auto listener : _listenerList)
		{	
			listener->onTankJoyStickDeactivated(this);
		}

		if (DPadKeyCode::NONE != _preKeyCode)
		{
			_preKeyCode = DPadKeyCode::NONE;
		}
	}
	else if (sender == _towerJoystick)
	{
		for (auto listener : _listenerList)
		{	
			listener->onTowerJoyStickDeactivated(this);
		}
	}	
	
	_curKeyCodeList.clear();
}

DPadKeyCode DPadLayer::_getDirectionID( const cocos2d::Point& _direction, float offsetValue, float _cradius )
{
	DPadKeyCode directionName;

	// xÓëyµÄ¾àÀë£¿
	float distance = abs(abs(_direction.x)-abs(_direction.y));

	if (_tankJoystick->getPower() < _cradius)
	{
		directionName = DPadKeyCode::CENTER;
		return directionName;
	}

	if(_direction.y<0 && _direction.x>-offsetValue && _direction.x<offsetValue)
	{
		directionName = DPadKeyCode::DOWN;
	}
	else if(_direction.y>0 && _direction.x>-offsetValue && _direction.x<offsetValue)
	{
		directionName = DPadKeyCode::UP;
	}
	else if(_direction.x>0 && _direction.y>-offsetValue && _direction.y<offsetValue)
	{
		directionName = DPadKeyCode::RIGHT;
	}
	else if(_direction.x<0 && _direction.y>-offsetValue && _direction.y<offsetValue)
	{
		directionName = DPadKeyCode::LEFT;
	}
	else if(_direction.x<0 && _direction.y<0 && distance<offsetValue)
	{
		directionName = DPadKeyCode::DOWNLEFT;
	}
	else if(_direction.x>0 && _direction.y<0 && distance<offsetValue)
	{
		directionName = DPadKeyCode::DOWNRIGHT;
	}
	else if(_direction.x<0 && _direction.y>0 && distance<offsetValue)
	{
		directionName = DPadKeyCode::UPLEFT;
	}
	else if(_direction.x>0 && _direction.y>0 && distance<offsetValue)
	{
		directionName = DPadKeyCode::UPRIGHT;
	}
	return directionName;
}

const std::vector<DPadKeyCode>& DPadLayer::getCurrentCommand() const
{
	return _curKeyCodeList;
}

DPadKeyCode DPadLayer::getKeyCode() const
{
	return _preKeyCode;
}

cocos2d::Point DPadLayer::getMouse() const
{
	return _mouse;
}

