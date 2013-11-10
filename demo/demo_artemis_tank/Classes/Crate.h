#ifndef __CRATE_H__
#define __CRATE_H__

// artemis
#include "include\ComponentType.h"

// cocos2dx
#include "ccTypes.h"
NS_CC_BEGIN
class Sprite;
NS_CC_END

// game
#include "Spatial.h"
class Physics;

class Crate : public Spatial
{
public:
	Crate(artemis::World* world, artemis::Entity* owner);
	virtual ~Crate();

public: // spatial
	virtual void initalize() override;
	virtual void render(cocos2d::DrawNode* graphics) override;
	virtual cocos2d::Node* getMaterial() const;

private:
	Physics* _physics;
	cocos2d::Sprite* _material;
};


#endif // __CRATE_H__