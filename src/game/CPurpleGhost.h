//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CPURPLEGHOST_H
#define PA2_2_SEMESTRALKA_CPURPLEGHOST_H

#include "CGhost.h"
#include "CMap.h"
#include "../SCoordinates.h"
#include "SMainEntitiesInfo.h"
#include "CGameInfo.h"

/// CPurpleGhost is class that represents purple ghost
class CPurpleGhost : public CGhost {
    const int inFront = 4; ///< How many tiles in front of player is the target
    bool began = false; ///< if the ghost has already began to move
    float beganTreshold = 0.001f; ///< how big must be the ratio of picked bonuses so the purple ghost will start moving

protected:
    /// Specific implementation of CGhost method for Purple Ghost
    SCoordinates getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;
public:
    /// A constructor constructs new Purple Ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CPurpleGhost(const CMap &map, const SCoordinates &homeLocation);
    /// It does Purple Ghost move behaviour, overrides the basic CGhost move
    SCoordinates move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;
    /// Method implements CGhost virtual method
    SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const override;
};

#endif //PA2_2_SEMESTRALKA_CPURPLEGHOST_H