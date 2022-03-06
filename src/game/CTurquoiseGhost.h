//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CTURQUOISEGHOST_H
#define PA2_2_SEMESTRALKA_CTURQUOISEGHOST_H

#include "CGhost.h"
#include "CMap.h"
#include "CGameInfo.h"
#include "SMainEntitiesInfo.h"


class CTurquoiseGhost : public CGhost {
    const int inFront = 2; ///< how many tiles in front of the player is the main point for calculating target
    bool began = false; ///< if the ghost has already began to move
    float beganTreshold = 0.1f; ///< how big must be the ratio of picked bonuses so the purple ghost will start moving
protected:
    /// Specific implementation of CGhost method for Turquoise Ghost
    SCoordinates getTargetCoordinates(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;

public:
    /// A constructor constructs new Turquoise Ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CTurquoiseGhost(const CMap &map, const SCoordinates &homeLocation);
    /// Method implements CGhost virtual method
    SCoordinates move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;
    /// It does Turquoise Ghost move behaviour, overrides the basic CGhost move
    SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const override;
};

#endif //PA2_2_SEMESTRALKA_CTURQUOISEGHOST_H