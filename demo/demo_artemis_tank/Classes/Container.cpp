#include "Container.h"

void Container::onEnter()
{
	Layer::onEnter();

	for (auto delegate : _listenerList) 
	{
		delegate->onContainerAdded(*this);
	}
}

void Container::onExit()
{
	Layer::onExit();

	for (auto delegate : _listenerList) 
	{
		delegate->onContainerRemoved(*this);
	}
}
