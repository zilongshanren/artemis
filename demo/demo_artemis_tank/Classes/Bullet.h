#ifndef __BULLET_H__
#define __BULLET_H__

// artemis
#include "ComponentType.h"

// cocos2dx
#include "cocos2d.h"

// game
#include "Spatial.h"
class Physics;

class Bullet : public Spatial
{
public:
	Bullet(artemis::World* world, artemis::Entity* owner);
	virtual ~Bullet();

public: // spatial
	virtual void initalize() override;
	virtual void render(cocos2d::DrawNode* graphics) override;
	virtual cocos2d::Node* getMaterial() const;

private:
	Physics* _physics;
	cocos2d::Sprite* _material;
};


#endif // __BULLET_H__