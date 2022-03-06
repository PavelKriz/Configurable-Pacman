//
// Created by pavel on 04.06.20.
//

#ifndef PA2_2_SEMESTRALKA_SMAINENTITIESINFO_H
#define PA2_2_SEMESTRALKA_SMAINENTITIESINFO_H

#include "CMovingObject.h"

/// Structure holds informations important for some entities behaviour
struct SMainEntityInfo{
    CMovingObject::EDirection direction_;
    SCoordinates coordinates_;
};

/// Structure with main ghost and player
struct SMainEntitiesInfo{
    SMainEntityInfo playerInfo_;
    SMainEntityInfo mainGhostInfo_;
};

#endif //PA2_2_SEMESTRALKA_SMAINENTITIESINFO_H