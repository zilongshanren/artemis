#ifndef __TANKZ_H__
#define __TANKZ_H__

// cocos2dx
#include "cocos2d.h"

class FrontTrack;
class Tankz : public cocos2d::Sprite
{
public:
	Tankz();
	~Tankz();

public: // cocos2dx
	CREATE_FUNC(Tankz);
	virtual bool init() override;

public: 
	cocos2d::Sprite* getTower() const;
	FrontTrack* getFrontTrackL() const;
	FrontTrack* getFrontTrackR() const;

private:
	cocos2d::Sprite* _tower;
	cocos2d::Sprite* _barrels;

	FrontTrack* _frontTrackL;
	FrontTrack* _frontTrackR;



};

class FrontTrack  : public cocos2d::Sprite
{
public: // cocos2dx
	CREATE_FUNC(FrontTrack);
	virtual bool init() override;
};

class TankTrack : public cocos2d::Node
{
public:

public: // cocos2dx
	static TankTrack* create(cocos2d::Size clipSize);
	virtual bool initWithClipSize(cocos2d::Size clipSize);
};


#endif // __TANKZ_H__