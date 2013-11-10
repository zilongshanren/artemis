#include "SoundFile.h"

SoundFile::SoundFile( const char* audioFile, SoundType type )
	: _soundFile(audioFile)
	, _soundType(type)
{

}

const char* SoundFile::getSoundFile() const
{
	return _soundFile.c_str();
}

SoundType SoundFile::getSoundType() const
{
	return _soundType;
}
