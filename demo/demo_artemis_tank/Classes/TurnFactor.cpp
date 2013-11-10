#include "TurnFactor.h"

TurnFactor::TurnFactor()
	: _factor(0.0f)
{

}

void TurnFactor::setFactor( float factor )
{
	this->_factor = factor;
}

float TurnFactor::getFactor() const
{
	return this->_factor;
}
