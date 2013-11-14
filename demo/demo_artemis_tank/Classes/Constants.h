#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// artemis
#include "ComponentType.h"

// cocos2dx
#include "cocos2d.h"

namespace Constants
{
	class UI
	{
	public:
		static cocos2d::Size designSize;
		static cocos2d::Size stageSize;
	};

	// artemis分组
	class Groups
	{
	public:
		static const char* BULLET;
		static const char* CRATE;
		static const char* PLAYER;
		static const char* TANK;
		static const char* WALL;
	};

	// artemis组件分类 
	class ComponentType
	{
	public:
		static artemis::ComponentType AMMO;
		static artemis::ComponentType DIRTY;
		static artemis::ComponentType HEALTH;
		static artemis::ComponentType PHYSICS;
		static artemis::ComponentType SCALEANIMATION;
		static artemis::ComponentType SOUNDFILE;
		static artemis::ComponentType SPATIALFORM;
		static artemis::ComponentType TOWER;
		static artemis::ComponentType TRANSFORM;
		static artemis::ComponentType TURNFACTOR;
		static artemis::ComponentType VELOCITY;
	};

	// 游戏各个界面的ZOrder，统一设置 
	enum class ZOrder
	{
		None = 0,
		TerrainRenderSystem,
		GameEntity,
		HealthRenderSystem,
		HubRenderSystem,
		DPadLayer,
	};

	// 物理引擎的碰撞筛选 
	class CategoryBitmask
	{
	public:
		static const int BULLET = 1 << 1;
		static const int CRATE  = 1 << 2;
		static const int TANK   = 1 << 3;
		static const int WALL   = 1 << 4;
		static const int WORLD  = 1 << 5;
		static const int ALL    = CRATE|WALL|BULLET|TANK|WORLD;
	};
};


#endif // __CONSTANTS_H__