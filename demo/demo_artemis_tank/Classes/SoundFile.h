#ifndef __SOUND_FILE_H__
#define __SOUND_FILE_H__

// C++
#include <string>

// artemis
#include "Component.h"

enum class SoundType
{
	UNKNOWN = 0,
	BGM,
	SE
};

// Ãû³Æ£ºÉùÒô
class SoundFile : public artemis::Component
{
public:
	SoundFile(const char* audioFile, SoundType type);
	const char* getSoundFile() const;
	SoundType getSoundType() const;

private:
	std::string _soundFile;
	SoundType   _soundType;
};


#endif // __SOUND_FILE_H__