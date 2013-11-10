#include "StatusBar.h"

// cocos2dx
#include "label_nodes/CCLabelBMFont.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "misc_nodes/CCProgressTimer.h"
#include "sprite_nodes/CCSprite.h"
USING_NS_CC;

// game
#include "Constants.h"
#include "GradientColorUtil.h"

StatusBar::StatusBar()
	: _title(nullptr)
	, _progress(nullptr)
{

}

StatusBar::~StatusBar()
{

}

StatusBar* StatusBar::create( const char* title, float percent)
{
	auto bar = new StatusBar;
	if (bar && bar->init(title, percent))
	{
		bar->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(bar);
	}
	return bar;
}

bool StatusBar::init( const char* title, float percent )
{
	do 
	{
		CC_BREAK_IF(!Node::init());
		
		// 能量条背景 
		auto statusBar = Sprite::create("statusBar.png");
		statusBar->setAnchorPoint(Point::ZERO);
		statusBar->setPosition(Point::ZERO);
		statusBar->setColor(Color3B::WHITE);
		statusBar->setOpacity(255.0f*0.2f);
		addChild(statusBar);

		_progress = ProgressTimer::create(Sprite::create("statusBar.png"));
		_progress->setType(ProgressTimer::Type::BAR);
		_progress->setMidpoint(Point::ZERO);
		_progress->setBarChangeRate(Point(1, 0));
		_progress->setAnchorPoint(Point::ZERO);
		_progress->setPosition(Point::ZERO);
		addChild(_progress);

		auto designSize    = Constants::UI::designSize;
		auto statusBarSize = statusBar->getContentSize();

		// 标题 
		_title = LabelBMFont::create();
		_title->setAnchorPoint(Point(0.0f, 0.0f));
		_title->setPosition(Point(0.0f, statusBarSize.height));
		_title->setFntFile("fonts/normal.fnt");
		addChild(_title);
 
		this->setContentSize(Size(designSize.width*0.5f, statusBar->getContentSize().height));
		this->setAnchorPoint(Point::ZERO);

		this->setTitle(title);
		this->setPercent(percent);
		return true;
	} while (0);
	return false;
}

void StatusBar::setPercent( float percent )
{
	percent = MAX(percent, 0.0f);
	percent = MIN(percent, 100.0f);
	_progress->setPercentage(percent);
	_progress->setColor(GradientColorUtil::getGradientColor(percent));
}

void StatusBar::setTitle( const char* title )
{
	if (nullptr == title)
	{
		title = "No Title";
	}
	_title->setString(title);
}
