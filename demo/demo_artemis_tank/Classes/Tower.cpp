#include "Tower.h"

Tower::Tower()
	: _rotation(0.0f)
	, _recoil(0.0f)
	, _turnThrust(1.0f)
{

}

float Tower::getRotation() const
{
	return _rotation;
}

void Tower::setRotation( float rotation )
{
	_rotation = rotation;
}

void Tower::addRotation( float angle )
{
	_rotation = int(_rotation + angle) % 360;
}

void Tower::setRecoil( float recoil )
{
	_recoil = recoil;
}

float Tower::getRecoil()
{
	return _recoil;
}

float Tower::getTurnThrust() const
{
	return _turnThrust;
}
