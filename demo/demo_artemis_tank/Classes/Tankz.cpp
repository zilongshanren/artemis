#include "Tankz.h"

// cocos2dx
#include "actions\CCActionInstant.h"
#include "actions\CCActionInterval.h"
#include "misc_nodes\CCClippingNode.h"
#include "draw_nodes\CCDrawNode.h"
USING_NS_CC;

Tankz::Tankz()
{

}

Tankz::~Tankz()
{

}

bool Tankz::init()
{
	do 
	{
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName("base.png"));

		auto rearTracks = Sprite::createWithSpriteFrameName("rearTracks.png");
		rearTracks->setAnchorPoint(Point::ZERO);
		addChild(rearTracks, -1);

		auto backTrackL = TankTrack::create(Size(62, 11));
		backTrackL->setAnchorPoint(Point::ZERO);
		backTrackL->setPosition(Point(10.0f, 119.0f));
		addChild(backTrackL, -1);

		auto backTrackR = TankTrack::create(Size(62, 11));
		backTrackR->setAnchorPoint(Point::ZERO);
		backTrackR->setPosition(Point(10.0f, 39.0f));
		addChild(backTrackR, -1);

		_frontTrackL = FrontTrack::create();
		_frontTrackL->setPosition(Point(125.0f, 125.0f));
		addChild(_frontTrackL, 3);

		_frontTrackR = FrontTrack::create();
		_frontTrackR->setFlippedY(true);
		_frontTrackR->setPosition(Point(125.0f, 39.0f));
		addChild(_frontTrackR, 3);
		
		_tower = Sprite::createWithSpriteFrameName("tower.png");
		auto towerSize = _tower->getContentSize();
		_tower->setPosition(Point(_contentSize.width*0.5f, _contentSize.height*0.5f));
		addChild(_tower, 4);

		_barrels = Sprite::createWithSpriteFrameName("barrels.png");
		_barrels->setAnchorPoint(Point(0.0f, 0.5f));
		_barrels->setPosition(Point(towerSize.width*0.8f, towerSize.height*0.5f));
		_tower->addChild(_barrels, -1);

		return true;
	} while (0);
	return false;
}

cocos2d::Sprite* Tankz::getTower() const
{
	return _tower;
}

FrontTrack* Tankz::getFrontTrackL() const
{
	return _frontTrackL;
}

FrontTrack* Tankz::getFrontTrackR() const
{
	return _frontTrackR;
}

bool FrontTrack::init()
{
	do 
	{
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName("leftFrontTrackCover.png"));

		auto frontTrack = Sprite::createWithSpriteFrameName("frontTrack.png");
		frontTrack->setPosition(Point(_contentSize.width*0.5f, _contentSize.height*0.5f));
		addChild(frontTrack, -1);

		auto tracks = TankTrack::create(Size(38, 11));
		tracks->setPosition(Point(_contentSize.width*0.5f, _contentSize.height*0.5f));
		addChild(tracks, -1);
		return true;
	} while (0);
	return false;
}

TankTrack* TankTrack::create( cocos2d::Size clipSize )
{
	auto track = new TankTrack;
	if (track && track->initWithClipSize(clipSize))
	{
		track->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(track);
	}
	return track;
}

bool TankTrack::initWithClipSize( cocos2d::Size clipSize )
{
	do 
	{
		CC_BREAK_IF(!Node::init());

		auto stencil = DrawNode::create();
		Point triangle[4];
		triangle[0] = Point::ZERO;
		triangle[1] = Point(0, clipSize.height);
		triangle[2] = Point(clipSize.width, clipSize.height);
		triangle[3] = Point(clipSize.width, 0);
		stencil->drawPolygon(triangle, 4, Color4F::WHITE, 0, Color4F::WHITE);

		auto clipper = ClippingNode::create();
		clipper->setAnchorPoint(Point::ZERO);
		clipper->setStencil(stencil);
		this->addChild(clipper);

		auto content = Sprite::createWithSpriteFrameName("tracks.png");
		auto contentSize = content->getContentSize();
		content->setAnchorPoint(Point::ZERO);
		content->runAction(RepeatForever::create(
			Sequence::createWithTwoActions(
			Place::create(Point::ZERO),
			MoveBy::create(0.5f, Point(-(contentSize.width-clipSize.width), 0.0f))
			)));
		clipper->addChild(content);

		clipSize.width   = MIN(contentSize.width, clipSize.width);
		clipSize.height  = MIN(contentSize.height, clipSize.height);
		setContentSize(clipSize);
		setAnchorPoint(Point(0.5f, 0.5f));
		return true;
	} while (0);
	return false;
}
