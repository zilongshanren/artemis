#include "ScaleAnimation.h"

ScaleAnimation::ScaleAnimation()
	: _minScale(1.0f)
	, _maxScale(1.0f)
	, _scale(1.0f)
	, _speed(0.0f)
	, _repeat(false)
	, _active(false)
{

}

float ScaleAnimation::getMinScale() const
{
	return _minScale;
}

void ScaleAnimation::setMinScale( float s )
{
	_minScale = s;
}

float ScaleAnimation::getMaxScale() const
{
	return _maxScale;
}

void ScaleAnimation::setMaxScale( float s )
{
	_maxScale = s;
}

float ScaleAnimation::getScale() const
{
	return _scale;
}

void ScaleAnimation::setScale( float s )
{
	_scale = s;
}

void ScaleAnimation::increaseScale( float s )
{
	_scale += s;
	if (_scale > _maxScale)
	{
		this->setScale(_maxScale);
		this->setActive(false);
	}
	else if (_scale < _minScale)
	{
		this->setScale(_minScale);
		this->setActive(false);
	}
}

float ScaleAnimation::getSpeed() const
{
	return _speed;
}

void ScaleAnimation::setSpeed( float s )
{
	_speed = s;
}

bool ScaleAnimation::isRepeat() const
{
	return _repeat;
}

void ScaleAnimation::setRepeat( bool b )
{
	_repeat = b;
}

bool ScaleAnimation::isActive() const
{
	return _active;
}

void ScaleAnimation::setActive( bool b )
{
	_active = b;
}
