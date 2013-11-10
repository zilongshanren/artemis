#include "SpatialForm.h"

SpatialForm::SpatialForm( const char* name )
	: _name(name)
{

}

const char* SpatialForm::getSpatialFormFile() const
{
	return _name.c_str();
}