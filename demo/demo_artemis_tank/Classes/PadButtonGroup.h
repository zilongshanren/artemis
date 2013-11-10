#ifndef __PAD_BUTTON_GROUP_H__
#define __PAD_BUTTON_GROUP_H__

// cocos2dx
#include "menu_nodes\CCMenu.h"

// template
#include "ListenerList.h"

// listener
class PadButtonListener 
{
public:
	virtual void onPadButtonPressed(cocos2d::Node* sender) = 0;
	virtual void onPadButtonReleased(cocos2d::Node* sender) = 0;
};

class PadButtonGroup
	: public cocos2d::Menu
	, public ListenerList<PadButtonListener*>
{
public:
	PadButtonGroup();
	~PadButtonGroup();

public: // cocos2dx
	CREATE_FUNC(PadButtonGroup);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) override;
};


#endif // __PAD_BUTTON_GROUP_H__