#ifndef __SCALE_ANIMATION_H__
#define __SCALE_ANIMATION_H__

#include "Component.h"
class ScaleAnimation : public artemis::Component
{
public:
	ScaleAnimation();

public:
	float getMinScale() const;
	void setMinScale(float s);

	float getMaxScale() const;
	void setMaxScale(float s);

	float getScale() const;
	void setScale(float s);
	void increaseScale(float s);

	float getSpeed() const;
	void setSpeed(float s);

	bool isRepeat() const;
	void setRepeat(bool b);

	bool isActive() const;
	void setActive(bool b);

private:

	float _minScale;
	float _maxScale;
	float _scale;
	float _speed;
	bool _repeat;
	bool _active;
};


#endif // __SCALE_ANIMATION_H__