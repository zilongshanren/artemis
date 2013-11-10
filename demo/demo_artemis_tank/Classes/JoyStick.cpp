#include "JoyStick.h" 

// C++
#include <algorithm>

// cocso2dx
#include "cocos2d.h"
USING_NS_CC;

JoyStick::JoyStick()
: _ball(0)
, _stick(0)
, _dock(0)
, _moveAreaRadius(0)
, _ballRadius(0)
, _followTouch(false)
, _autoHide(false)
, _activeRadius(0)
, _touching(false)
, _hasAnimation(false)
, _power(0.0f)
, _angle(0.0f)
{
	_direction = Point::ZERO;
	_currentPoint = Point::ZERO;
	_activeRect = Rect::ZERO;
}

JoyStick::~JoyStick()
{

}

JoyStick* JoyStick::create( int ballRadius, int moveAreaRadius, bool followTouch, bool visible, bool autoHide, bool hasAnimation )
{
	auto joystick = new JoyStick;
	if (joystick && joystick->initWithBallRadius(ballRadius, moveAreaRadius, followTouch, visible, autoHide, hasAnimation))
	{
		joystick->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(joystick);
	}
	return joystick;
}

bool JoyStick::initWithBallRadius( int ballRadius, int moveAreaRadius, bool followTouch, bool visible, bool autoHide, bool hasAnimation )
{
	do 
	{
		CC_BREAK_IF(!Layer::init());

		_ballRadius = ballRadius; 
		_moveAreaRadius = moveAreaRadius; 
		_followTouch = followTouch; 
		_visible = visible; 
		_autoHide = autoHide; 
		_hasAnimation = hasAnimation; 

		_power = 0.0f; 
		_angle = 0.0f; 

		auto winSize = Director::getInstance()->getWinSize(); 
		setHitAreaWithRect(Rect(0.0f, 0.0f, winSize.width*0.5f, winSize.height*0.5f)); 

		_ball  = Sprite::create();
		_stick = Sprite::create();
		_dock  = Sprite::create();

		addChild(this->_dock);
		addChild(this->_stick);
		addChild(this->_ball);
		
		if (!visible || autoHide)
		{
			setVisible(false);
		}

		setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
		setTouchEnabled(true);

		return true;
	} while (0);
	return false;
}

bool JoyStick::onTouchBegan( Touch* touch, Event* event )
{
	if (!_containsTouchLocation(touch)) 
	{ 
		return false; 
	} 

	auto location = touch->getLocation();
	_onTouchBegan(location); 
	return true; 
}

void JoyStick::onTouchMoved( Touch* touch, Event* event )
{
	if (_touching) 
	{ 
		auto location = touch->getLocation();
		_updateTouchPoint(location); 
	} 
}

void JoyStick::onTouchEnded( Touch* touch, Event* event )
{
	if (_touching) 
	{ 
		if(_autoHide && _visible)
		{ 
			setVisible(false); 
		} 

		_touching = false; 
		
		_stopTimer(); 
		_resetTexturePosition(); 
	} 
}

void JoyStick::onTouchCancelled( cocos2d::Touch* touch, cocos2d::Event* event )
{
	onTouchEnded(touch, event);
}

void JoyStick::setBallTexture( const char* imageName )
{
	_ball->initWithFile(imageName); 
}

void JoyStick::setBallTexutreWithFrameName( const char* spriteFrameName )
{
	_ball->initWithSpriteFrameName(spriteFrameName);
}

void JoyStick::setStickTexture( const char* imageName )
{
	auto stick = CCSprite::create(imageName); 
	stick->setPosition(Point(stick->getContentSize().width*0.5f, 0.0f)); 

	_stick->removeAllChildrenWithCleanup(true); 
	_stick->addChild(stick, 0, kTagSprStick); 
	_stick->setScaleX( _ball->getPosition().getDistance(Point::ZERO) / stick->getTextureRect().size.width );
}

void JoyStick::setSitckTextureWithFrameName( const char* spriteFrameName )
{
	auto stick = CCSprite::createWithSpriteFrameName(spriteFrameName); 
	stick->setPosition(Point(stick->getContentSize().width*0.5f, 0.0f)); 

	_stick->removeAllChildrenWithCleanup(true); 
	_stick->addChild(stick, 0, kTagSprStick); 
	_stick->setScaleX( _ball->getPosition().getDistance(Point::ZERO) / stick->getTextureRect().size.width );
}

void JoyStick::setDockTexture( const char* imageName )
{
	_dock->initWithFile(imageName);
}

void JoyStick::setDockTextureWithFrameName( const char* spriteFrameName )
{
	_dock->initWithSpriteFrameName(spriteFrameName);
}

void JoyStick::setHitAreaWithRadius( int radius )
{
	_activeRect   = Rect::ZERO; 
	_activeRadius = radius; 
}

void JoyStick::setHitAreaWithRect( cocos2d::Rect hitAreaRect )
{
	_activeRect   = hitAreaRect; 
	_activeRadius = 0; 
}

void JoyStick::_startTimer()
{
	for(auto listener : _listenerList)
	{
		listener->onJoyStickActivated(this); 
	}

	schedule(schedule_selector(JoyStick::_timerUpdate)); 
}

void JoyStick::_stopTimer()
{
	for(auto listener : _listenerList)
	{
		listener->onJoyStickDeactivated(this); 
	}

	unschedule(schedule_selector(JoyStick::_timerUpdate)); 
}

void JoyStick::_timerUpdate( float dt )
{
	for(auto listener : _listenerList)
	{
		listener->onJoyStickUpdate(this, _angle,  _direction, _power); 
	}
}

void JoyStick::_onTouchBegan( Point& touchPoint )
{
	_currentPoint = touchPoint; 
	_touching = true; 

	if(_autoHide && _visible)
	{ 
		setVisible(true); 
	} 

	if(_followTouch)
	{ 
		setPosition(touchPoint); 
	} 

	_ball->stopAllActions(); 
	_updateTouchPoint(touchPoint); 
	_startTimer(); 
}

void JoyStick::_resetTexturePosition()
{
	_power = 0.0f; 
	_angle = 0.0f; 

	_currentPoint = Point::ZERO;
	_stick->setPosition(Point::ZERO); 
	_stick->setScaleX(_power); 

	if (!_autoHide && _visible && _hasAnimation)
	{ 
		auto action = MoveTo::create(0.5f, Point::ZERO); 
		_ball->runAction(EaseElasticOut::create(action)); 
	}
	else
	{ 
		_ball->setPosition(Point::ZERO); 
	} 
}

bool JoyStick::_containsTouchLocation( Touch* touch )
{
	auto touchPoint = touch->getLocation(); 
	if ( _activeRadius > 0 ) 
	{ 
		auto selfposition = getParent()->convertToWorldSpace(getPosition()); 
		if (touchPoint.getDistance(selfposition) < _activeRadius)
		{ 
			return true; 
		} 
	} 

	if( _activeRect.size.width > 0 && _activeRect.size.height > 0)
	{ 
		if (touchPoint.x > _activeRect.origin.x &&
			touchPoint.x < _activeRect.origin.x + _activeRect.size.width &&
			touchPoint.y > _activeRect.origin.y &&
			touchPoint.y < _activeRect.origin.y + _activeRect.size.height) 
		{ 
			return true; 
		} 
	} 
	return false; 
}

void JoyStick::_updateTouchPoint( Point& touchPoint )
{
	auto selfposition = getParent()->convertToWorldSpace(getPosition()); 
	auto xxxPoint = touchPoint - selfposition;

	int radius = _moveAreaRadius - _ballRadius;
	if ( touchPoint.getDistance(selfposition) > radius ) 
	{ 
		_currentPoint = xxxPoint.normalize() * radius; 
	}
	else
	{ 
		_currentPoint= xxxPoint; 
	} 
	_ball->setPosition(_currentPoint); 

	// ¹öÇòÀïÔ²ÐÄµÄ¾àÀë
	float ballDistance = _ball->getPosition().getDistance(Point::ZERO);
	_angle = atan2(_ball->getPositionY(), _ball->getPositionX()) / (M_PI/180.0f); 
	_power =  ballDistance / radius; 
	_direction.x = cos(CC_DEGREES_TO_RADIANS(_angle));
	_direction.y = sin(CC_DEGREES_TO_RADIANS(_angle)); 

	auto stick = (Sprite*)_stick->getChildByTag(kTagSprStick); 
	_stick->setScaleX(ballDistance / stick->getTextureRect().size.width); 
	_stick->setRotation(-_angle); 
}

int JoyStick::getPower() const
{
	return _power;
}
