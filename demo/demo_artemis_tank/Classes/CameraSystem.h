#ifndef __CAMERA_SYSTEM_H__
#define __CAMERA_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\EntitySystem.h"

// cocos2dx
#include "layers_scenes_transitions_nodes\CCLayer.h"
NS_CC_BEGIN
class Node;
NS_CC_END

// game
#include "PlayerEntitySystem.h"
#include "Physics.h"

class Container;
class CameraSystem : public PlayerEntitySystem
{
public:
	CameraSystem(Container* container);
	~CameraSystem();
	
public: // artemis
	virtual void initialize() override;

protected: // artemis
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) override;
	virtual bool checkProcessing() override;

private:
	void updatePosition();
	void updateZoom();
	void fixBoundaries();

public: 
	float getOffsetX() const;
	float getOffsetY() const;
	float getStartX() const;
	float getStartY() const;
	float getEndX() const;
	float getEndY() const;
	float getWidth() const;
	float getHeight() const;
	float getZoom() const;
	bool isDirty() const;
	void setDirty(bool dirty);

private:
	cocos2d::Node* _graphics;

	float _lookAtX;
	float _lookAtY;

	float _targetZoom;
	float _zoom;
	bool _dirty;

	cocos2d::Size _screenSize;
	artemis::ComponentMapper<Physics> _physicsMapper;
};


#endif // __CAMERA_SYSTEM_H__