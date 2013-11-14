#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

// artemis
#include "ComponentMapper.h"
#include "ComponentType.h"

// cocos2dx
#include "ccTypes.h"

// game
#include "ScaleAnimation.h"
#include "Spatial.h"
#include "Transform.h"

class Explosion : public Spatial
{
public:
	Explosion(artemis::World* world, artemis::Entity* owner);
	virtual ~Explosion();

public: // spatial
	virtual void initalize() override;
	virtual void render(cocos2d::DrawNode* graphics) override;
	virtual cocos2d::Node* getMaterial() const;

private:
	Transform*      _transform;
	ScaleAnimation* _scaleAnimation;

	const static float RADIUS;
	const static cocos2d::Color4F COLOR;
};



#endif // __EXPLOSION_H__