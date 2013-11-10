#ifndef __SPATIAL_FORM_H__
#define __SPATIAL_FORM_H__

// C++
#include <string>

// artemis
#include "include\Component.h"

// Ãû³Æ£º¿Õ¼äÐÎÌ¬£¿
class SpatialForm : public artemis::Component
{
public:
	SpatialForm(const char* name);

public:
	const char* getSpatialFormFile() const;

private:
	std::string _name;
};


#endif // __SPATIAL_FORM_H__