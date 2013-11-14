#ifndef __CONTAINER_H__
#define __CONTAINER_H__

// C++
#include <vector>

// cocos2dx
#include "CCLayer.h"

// template
#include "ListenerList.h"

class Container;
class ContainerListener 
{
public:
	virtual void onContainerAdded(Container& container) = 0;
	virtual void onContainerRemoved(Container& container) = 0;
};

class DPadLayer;
class Container : public cocos2d::Layer, public ListenerList<ContainerListener*>
{
public: // cocos2dx
	virtual void onEnter() override;
	virtual void onExit() override;

public: // interface
	virtual DPadLayer* getInput() const = 0;
	virtual cocos2d::Node* getGraphics() const = 0;
	virtual cocos2d::Node* getGUI() const = 0;
};

#endif // __CONTAINER_H__