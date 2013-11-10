#ifndef __SOUND_SYSTEM_H__
#define __SOUND_SYSTEM_H__

// artemis
#include "include\ComponentMapper.h"
#include "include\EntityProcessingSystem.h"

// game
#include "SoundFile.h"

class SoundSystem : public artemis::EntityProcessingSystem
{
public:
	SoundSystem();
	virtual void initialize() override;
	virtual void processEntity(artemis::Entity &e) override;
	virtual void added(artemis::Entity &e) override;

private:
	artemis::ComponentMapper<SoundFile> _soundMapper;

};


#endif // __SOUND_SYSTEM_H__