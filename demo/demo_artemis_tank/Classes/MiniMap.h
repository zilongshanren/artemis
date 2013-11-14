#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "CCSprite.h"
// artemis
#include "ComponentMapper.h"
#include "Entity.h"
#include "ImmutableBag.h"

// game
#include "Physics.h"

// cocos2dx
namespace cocos2d
{
	class DrawNode;
};

// game
class BoundarySystem;
class CameraSystem;

class MiniMap : public cocos2d::Sprite
{
public: // cocos2dx
	CREATE_FUNC(MiniMap);
	virtual bool init();

public:
	void render(
		CameraSystem* system,
		artemis::ImmutableBag<artemis::Entity*>* crate,
		artemis::ImmutableBag<artemis::Entity*>* tank,
		artemis::ComponentMapper<Physics>& physicsMapper);

private:
	cocos2d::DrawNode* _renderer;

	float _mapScaleX;
	float _mapScaleY;
};


#endif // __MINI_MAP_H__