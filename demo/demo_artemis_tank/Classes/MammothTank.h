#ifndef __MAMMOTH_TANK_H__
#define __MAMMOTH_TANK_H__

// artemis
#include "ComponentMapper.h"
#include "ComponentType.h"

// cocos2dx
#include "cocos2d.h"

// game
#include "Spatial.h"
#include "Transform.h"
class Physics;
class Velocity;
class TurnFactor;
class Tankz;
class Tower;

class MammothTank : public Spatial
{
public:
	MammothTank(artemis::World* world, artemis::Entity* owner);
	virtual ~MammothTank();

public: // spatial
	virtual void initalize() override;
	virtual void render(cocos2d::DrawNode* graphics) override;
	virtual cocos2d::Node* getMaterial() const;

private:
	Tankz*      _material;

	Physics*    _physics;
	Velocity*   _velocity;
	TurnFactor* _turnFactor;
	Tower*      _tower;
};


#endif // __MAMMOTH_TANK_H__