#ifndef __TOWER_H__
#define __TOWER_H__

// artemis
#include "include\Component.h"

// Ãû³Æ£ºÅÚËþ
class Tower : public artemis::Component
{
public:
	Tower();

public:
	float getRotation() const;
	void setRotation(float rotation);
	void addRotation(float angle);

	void setRecoil(float recoil);
	float getRecoil();

	float getTurnThrust() const;

private:
	float _rotation;
	float _recoil; // ºó×ùÁ¦ 
	float _turnThrust;
};


#endif // __TOWER_H__