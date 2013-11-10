#include "Transform.h"

// cocos2dx
#include "ccMacros.h"

Transform::Transform()
	: _x(0.0f)
	, _y(0.0f)
	, _rotation(0.0f)
{

}

Transform::Transform( float x, float y )
	: _x(x)
	, _y(y)
	, _rotation(0.0f)
{

}

Transform::Transform( float x, float y, float rotation )
	: _x(x)
	, _y(y)
	, _rotation(rotation)
{

}

void Transform::addX( float x )
{
	this->_x += x;
}

void Transform::addY( float y )
{
	this->_y += y;
}

float Transform::getX() const
{
	return this->_x;
}

void Transform::setX( float x )
{
	this->_x = x;
}

float Transform::getY() const
{
	return _y;
}

void Transform::setY( float y )
{
	this->_y = y;
}

void Transform::setLocation( float x, float y )
{
	this->_x = x;
	this->_y = y;
}

float Transform::getRotation() const
{
	return _rotation;
}

void Transform::setRotation( float rotation )
{
	this->_rotation = rotation;
}

void Transform::addRotation( float angle )
{
	this->_rotation = int(_rotation + angle) % 360;
}

float Transform::getRotationAsRadians() const
{
	return CC_DEGREES_TO_RADIANS(_rotation);
}
