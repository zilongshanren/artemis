#ifndef __TANKZ_GAME_INL__
#define __TANKZ_GAME_INL__

#include "TankzGame.h"

DPadLayer* TankzGame::getInput() const
{
	return _input;
}

cocos2d::Node* TankzGame::getGraphics() const
{
	return _graphics;
}
cocos2d::Node* TankzGame::getGUI() const
{
	return _gui;
}

#endif // __TANKZ_GAME_INL__