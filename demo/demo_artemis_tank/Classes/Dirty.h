#ifndef __DIRTY_H__
#define __DIRTY_H__

// artemis
#include "Component.h"

class Dirty : public artemis::Component
{
public:
	Dirty();

public:
	bool isDirty() const;
	void setDirty(bool dirty);

private:
	bool _dirty;
};


#endif // __DIRTY_H__