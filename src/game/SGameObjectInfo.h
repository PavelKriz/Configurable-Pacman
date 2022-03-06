//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_SGAMEOBJECTINFO_H
#define PA2_2_SEMESTRALKA_SGAMEOBJECTINFO_H

#include "../SCoordinates.h"
#include <stdint.h>


/// Enumeration of directions possible in the game
enum EGameObjectDirection {
    DIRECTION_LEFT, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, NO_DIRECTION
};

/// Enumeration of all possible game objects
enum EGameObject {
    GAMEOBJECT_PLAYER,
    GAMEOBJECT_RED_GHOST,
    GAMEOBJECT_TURQUOISE_GHOST,
    GAMEOBJECT_SIENA_GHOST,
    GAMEOBJECT_PURPLE_GHOST,
    GAMEOBJECT_CORONA_GHOST,
    GAMEOBJECT_MOVING_BONUS,
    GAMEOBJECT_BASIC_BONUS,
    GAMEOBJECT_KILLER_BONUS,
    GAMEOBJECT_WALL,
    GAMEOBJECT_GATE,
    GAMEOBJECT_EMPTY,
    GAMEOBJECT_KILLED_GHOST,
    GAMEOBJECT_SCARED_CORONA,
    GAMEOBJECT_SCARED_GHOST
};

/// Struct holds info about the game objects
struct SGameObjectInfo {
    SCoordinates location_; ///< location of the object
    EGameObject objectType_; ///< type of the object
    uint32_t additionalInfo_; ///< some additional info specific for each object
};

#endif //PA2_2_SEMESTRALKA_SGAMEOBJECTINFO_H