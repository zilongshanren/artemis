#include "DirtySystem.h"

DirtySystem::DirtySystem()
{
	addComponentType<Dirty>();
}

DirtySystem::~DirtySystem()
{

}

void DirtySystem::initialize()
{
	_dirtyMapper.init(*world);
	this->setPassive(true);
}

void DirtySystem::processEntity( artemis::Entity& e )
{
	auto dirty = _dirtyMapper.get(e);
	dirty->setDirty(false);
}

bool DirtySystem::checkProcessing()
{
	return true;
}
