#include "Physics.h"

// cocos2dx
#include "ccMacros.h"

Physics::Physics( cocos2d::PhysicsBody* body )
{
	this->_body = body;
	this->_body->retain();
}

Physics::~Physics()
{
	CC_SAFE_RELEASE(_body);
}

float Physics::getX() const
{
	return _body->getPosition().x;
}

float Physics::getY() const
{
	return _body->getPosition().y;
}

float Physics::getRotation() const
{
	return _body->getRotation();
}

void Physics::addRotation( float angle )
{
	_body->setRotation(int(_body->getRotation()+angle)%360);
}

void Physics::setLocation( float x, float y )
{
	_body->setPosition(cocos2d::Point(x, y));
}

float Physics::getRotationAsRadians() const
{
	return CC_DEGREES_TO_RADIANS(getRotation());
}

void Physics::setForce( float xf, float yf )
{
	_body->applyForce(cocos2d::Point(xf, yf));
}

cocos2d::PhysicsBody* Physics::getBody() const
{
	return _body;
}
