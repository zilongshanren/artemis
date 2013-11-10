#include "ScaleAnimationSystem.h"

// artemis
#include "include\Entity.h"

ScaleAnimationSystem::ScaleAnimationSystem()
{
	addComponentType<ScaleAnimation>();
}

ScaleAnimationSystem::~ScaleAnimationSystem()
{

}

void ScaleAnimationSystem::initialize()
{
	_scaleAnimationMapper.init(*world);
}

void ScaleAnimationSystem::processEntity( artemis::Entity &e )
{
	auto s = _scaleAnimationMapper.get(e);
	if (s->isActive()) 
	{
		s->increaseScale(s->getSpeed() * world->getDelta());
	}
	else
	{
		e.remove();
	}
}

bool ScaleAnimationSystem::checkProcessing()
{
	return true;
}
