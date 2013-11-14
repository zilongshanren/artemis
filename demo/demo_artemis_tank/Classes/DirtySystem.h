#ifndef __DIRTY_SYSTEM_H__
#define __DIRTY_SYSTEM_H__

// artemis
#include "ComponentMapper.h"
#include "EntityProcessingSystem.h"

// game
#include "Dirty.h"

class DirtySystem : public artemis::EntityProcessingSystem
{
public:
	DirtySystem();
	~DirtySystem();

public: // artemis
	virtual void initialize() override;
	virtual void processEntity(artemis::Entity& e) override;
	virtual bool checkProcessing() override;

private:

	artemis::ComponentMapper<Dirty> _dirtyMapper;
};


#endif // __DIRTY_SYSTEM_H__