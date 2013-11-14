#ifndef __WALL_H__
#define __WALL_H__

// artemis
#include "ComponentType.h"

// cocos2dx
#include "cocos2d.h"

// game
#include "Spatial.h"
class Physics;

class Wall : public Spatial
{
public:
	Wall(artemis::World* world, artemis::Entity* owner);
	virtual ~Wall();

public: // spatial
	virtual void initalize() override;
	virtual void render(cocos2d::DrawNode* graphics) override;
	virtual cocos2d::Node* getMaterial() const override;

private:
	Physics* _physics;
	cocos2d::Sprite* _material;
};


#endif // __WALL_H__