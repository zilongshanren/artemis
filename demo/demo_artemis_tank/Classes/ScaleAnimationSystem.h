#ifndef __SCALE_ANIMATION_SYSTEM_H__
#define __SCALE_ANIMATION_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\EntityProcessingSystem.h"

// game
#include "ScaleAnimation.h"

class ScaleAnimationSystem : public artemis::EntityProcessingSystem
{
public:
	ScaleAnimationSystem();
	virtual ~ScaleAnimationSystem();
	virtual void initialize() override;
	virtual void processEntity(artemis::Entity &e) override;
	virtual bool checkProcessing() override;

private:
	artemis::ComponentMapper<ScaleAnimation> _scaleAnimationMapper;
};

#endif // __SCALE_ANIMATION_SYSTEM_H__