#ifndef __INPUT_LAYER_H__
#define __INPUT_LAYER_H__

// cocos2dx
#include "layers_scenes_transitions_nodes\CCLayer.h"

// game
#include "JoyStick.h"

// template
#include "ListenerList.h"

// enum
enum class DPadKeyCode
{
	NONE      = 0,
	UP        = 1,
	UPRIGHT	  = 2,
	RIGHT     = 3,
	DOWNRIGHT = 4,
	DOWN      = 5,
	DOWNLEFT  = 6,
	LEFT      = 7,
	UPLEFT    = 8,
	CENTER    = 9,
	BUTTON_A  = 10,
};

class DPadListener
{
public:	
	virtual void onTankJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) = 0;
	virtual void onTankJoyStickActivated(cocos2d::Node* sender){ CC_UNUSED_PARAM(sender); }
	virtual void onTankJoyStickDeactivated(cocos2d::Node* sender) { CC_UNUSED_PARAM(sender); }

	virtual void onTowerJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) = 0;
	virtual void onTowerJoyStickActivated(cocos2d::Node* sender){ CC_UNUSED_PARAM(sender); }
	virtual void onTowerJoyStickDeactivated(cocos2d::Node* sender) { CC_UNUSED_PARAM(sender); }
};

// D-Pad
class DPadLayer 
	: public cocos2d::Layer
	, public JoyStickListener
	, public ListenerList<DPadListener*>
{
public:
	DPadLayer();
	virtual ~DPadLayer();
	
public: // cocos2dx
	CREATE_FUNC(DPadLayer);
	virtual bool init() override;

public: // joystick
	virtual void onJoyStickUpdate(cocos2d::Node* sender, float angle, cocos2d::Point direction, float power) override;
	virtual void onJoyStickActivated(cocos2d::Node* sender) override;
	virtual void onJoyStickDeactivated(cocos2d::Node* sender) override;

public: // getters
	const std::vector<DPadKeyCode>& getCurrentCommand() const;
	DPadKeyCode getKeyCode() const;
	cocos2d::Point getMouse() const;

private:
	DPadKeyCode _getDirectionID(const cocos2d::Point& _direction, float offsetValue, float _cradius);

private:

	// –Èƒ‚ Û±Í 
	cocos2d::Point _mouse;
	
	// “°∏À-ÃπøÀ
	JoyStick* _tankJoystick;

	// “°∏À-≈⁄Ã®
	JoyStick* _towerJoystick;

	// ¥Í’–”√ 
	DPadKeyCode _preKeyCode;
	std::vector<DPadKeyCode> _curKeyCodeList;
};


#endif // __INPUT_LAYER_H__