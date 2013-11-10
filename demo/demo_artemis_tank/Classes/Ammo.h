#ifndef __AMMO_H__
#define __AMMO_H__

// artemis
#include "include\Component.h"

// Ãû³Æ£ºµ¯Ò© 
class Ammo : public artemis::Component
{
public:
	Ammo(float ammo);
	Ammo(float ammo, float maximumAmmo);

public:
	float getAmmo() const;
	void setAmmo(float ammo);

	float getMaximumAmmo() const;
	void setMaximumAmmo(float ammo);

	float getAmmoStatus() const;
	bool hasAmmo(float hasAmmo);
	void reduceBy(float ammo);
	void addAmmo(float ammo);

private:
	float _ammo;
	float _maximumAmmo;
};


#endif // __AMMO_H__