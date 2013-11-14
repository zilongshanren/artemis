#include "Constants.h"

// artemis
#include "ComponentTypeManager.h"

// game
#include "Ammo.h"
#include "Health.h"
#include "Physics.h"
#include "SoundFile.h"
#include "SpatialForm.h"
#include "Tower.h"
#include "Transform.h"
#include "TurnFactor.h" 
#include "Velocity.h"

const char* Constants::Groups::BULLET = "bullets";
const char* Constants::Groups::CRATE  = "crates";
const char* Constants::Groups::PLAYER = "PLAYER";
const char* Constants::Groups::TANK   = "tanks";
const char* Constants::Groups::WALL   = "walls";

cocos2d::Size Constants::UI::designSize(640.0f, 960.0f);
cocos2d::Size Constants::UI::stageSize(2160.0f, 2160.0f);

artemis::ComponentType Constants::ComponentType::AMMO       ;
artemis::ComponentType Constants::ComponentType::DIRTY      ;
artemis::ComponentType Constants::ComponentType::HEALTH     ;
artemis::ComponentType Constants::ComponentType::PHYSICS    ;
artemis::ComponentType Constants::ComponentType::SCALEANIMATION;
artemis::ComponentType Constants::ComponentType::SOUNDFILE  ;
artemis::ComponentType Constants::ComponentType::SPATIALFORM;
artemis::ComponentType Constants::ComponentType::TOWER      ;
artemis::ComponentType Constants::ComponentType::TRANSFORM  ;
artemis::ComponentType Constants::ComponentType::TURNFACTOR ;
artemis::ComponentType Constants::ComponentType::VELOCITY   ;

