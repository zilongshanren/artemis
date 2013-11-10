#include "MiniMap.h"

// cocos2dx
#include "cocoa\CCGeometry.h"
USING_NS_CC;

// cocos2dx
#include "draw_nodes/CCDrawNode.h"

// game
#include "CameraSystem.h"
#include "Constants.h"

bool MiniMap::init()
{
	do 
	{
		CC_BREAK_IF(!Sprite::initWithFile("minimapBg.png"));

		_renderer = DrawNode::create();
		addChild(_renderer);

		auto stageSize = Constants::UI::stageSize;
		_mapScaleX = _contentSize.width / stageSize.width;
		_mapScaleY = _contentSize.height / stageSize.height;

		return true;
	} while (0);
	return false;
}

void MiniMap::render( 
	CameraSystem* cs,
	artemis::ImmutableBag<artemis::Entity*>* crates,
	artemis::ImmutableBag<artemis::Entity*>* tanks,
	artemis::ComponentMapper<Physics>& pm)
{
	_renderer->clear();

	float x1 = _mapScaleX*cs->getStartX();
	float y1 = _mapScaleY*cs->getStartY();
	float x2 = x1+_mapScaleX*cs->getWidth();
	float y2 = y1+_mapScaleY*cs->getHeight();
	Point vertices[] = { Point(x1,y1), Point(x1,y2), Point(x2,y2), Point(x2,y1)};
	_renderer->drawPolygon(vertices, 4, Color4F(0,0,0,0), 1, Color4F::WHITE);

	Point point = Point::ZERO;
	for(int i=0, count=crates->getCount(); i<count; ++i) 
	{
		auto crate = crates->get(i);
		auto physics = pm.get(*crate);
		point.x = physics->getX()*_mapScaleX;
		point.y = physics->getY()*_mapScaleY;
		_renderer->drawDot(point, 2, Color4F::WHITE);
	}

	for(int i=0, count=tanks->getCount(); i<count; ++i) 
	{
		auto t = tanks->get(i);
		auto physics = pm.get(*t);
		point.x = physics->getX()*_mapScaleX;
		point.y = physics->getY()*_mapScaleY;
		_renderer->drawDot(point, 4, Color4F::GREEN);
	}
}
