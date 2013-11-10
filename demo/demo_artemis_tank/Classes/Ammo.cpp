#include "Ammo.h"

Ammo::Ammo( float ammo )
	: _ammo(ammo)
	, _maximumAmmo(ammo)
{

}

Ammo::Ammo( float ammo, float maximumAmmo )
	: _ammo(ammo)
	, _maximumAmmo(maximumAmmo)
{

}

float Ammo::getAmmo() const
{
	return this->_ammo; 
}

void Ammo::setAmmo( float ammo )
{
	this->_ammo = ammo;
}

float Ammo::getMaximumAmmo() const
{
	return this->_maximumAmmo;
}

void Ammo::setMaximumAmmo( float ammo )
{ 
	this->_maximumAmmo = ammo;
}

float Ammo::getAmmoStatus() const 
{ 
	return _ammo/_maximumAmmo*100.0f;;
}

bool Ammo::hasAmmo( float hasAmmo )
{
	return _ammo >= hasAmmo;
}

void Ammo::reduceBy( float ammo )
{
	this->_ammo -= ammo;
}

void Ammo::addAmmo( float ammo )
{
	this->_ammo += ammo;
	if (this->_ammo > _maximumAmmo)
	{
		this->_ammo = _maximumAmmo;
	}
}
