#ifndef __STATUS_BAR_H__
#define __STATUS_BAR_H__

// cocos2dx
#include "cocos2d.h"
NS_CC_BEGIN
class LabelBMFont;
class ProgressTimer;
NS_CC_END

class StatusBar : public cocos2d::Node
{
public:
	~StatusBar();

public: // cocos2dx
	static StatusBar* create(const char* title, float percent);
	virtual bool init(const char* title, float percent);

public:
	void setPercent(float percent);
	void setTitle(const char* title);

protected:
	StatusBar();

private:
	cocos2d::LabelBMFont* _title;
	cocos2d::ProgressTimer* _progress;

};


#endif // __STATUS_BAR_H__