#include "SoundSystem.h"

// cocos2dx
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

SoundSystem::SoundSystem()
{
	addComponentType<SoundFile>();
}

void SoundSystem::initialize()
{
	_soundMapper.init(*world);
}

void SoundSystem::processEntity( artemis::Entity &e )
{
	world->deleteEntity(e);
}

void SoundSystem::added( artemis::Entity &e )
{
	auto soundFile = _soundMapper.get(e);
	if (SoundType::BGM == soundFile->getSoundType())
	{
		 SimpleAudioEngine::getInstance()->playBackgroundMusic(soundFile->getSoundFile());
	}
	else if(SoundType::SE == soundFile->getSoundType())
	{
		SimpleAudioEngine::getInstance()->playEffect(soundFile->getSoundFile());
	}
}
