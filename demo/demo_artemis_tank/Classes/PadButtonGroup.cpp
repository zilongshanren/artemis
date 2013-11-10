#include "PadButtonGroup.h"

// C++
#include <algorithm>

PadButtonGroup::PadButtonGroup()
{

}

PadButtonGroup::~PadButtonGroup()
{

}

bool PadButtonGroup::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event )
{
	if (Menu::onTouchBegan(touch, event))
	{
		for (auto listener : _listenerList)
		{
			listener->onPadButtonPressed(_selectedItem);
		}

		return true;
	}
	return false;
}

void PadButtonGroup::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event )
{
	Menu::onTouchMoved(touch, event);

	for (auto listener : _listenerList)
	{
		listener->onPadButtonPressed(_selectedItem);
	}
}

void PadButtonGroup::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event )
{
	Menu::onTouchEnded(touch, event);

	for (auto listener : _listenerList)
	{
		listener->onPadButtonReleased(_selectedItem);
	}
}

void PadButtonGroup::onTouchCancelled( cocos2d::Touch* touch, cocos2d::Event* event )
{
	Menu::onTouchCancelled(touch, event);

	for (auto listener : _listenerList)
	{
		listener->onPadButtonReleased(_selectedItem);
	}
}