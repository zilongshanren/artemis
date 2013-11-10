#include "Dirty.h"

Dirty::Dirty()
	: _dirty(false)
{

}

bool Dirty::isDirty() const
{
	return _dirty;
}

void Dirty::setDirty( bool dirty )
{
	_dirty = dirty;
}
