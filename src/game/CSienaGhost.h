//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CSIENAGHOST_H
#define PA2_2_SEMESTRALKA_CSIENAGHOST_H

#include "CGhost.h"
#include "CMap.h"
#include "../SCoordinates.h"
#include "SMainEntitiesInfo.h"
#include "CGameInfo.h"

/// CSienaGhost is class that represents Siena Ghost
class CSienaGhost : public CGhost {
    bool began = false; ///< if the ghost has already began to move
    float beganTreshold = 0.3f; ///< how big must be the ratio of picked bonuses so the purple ghost will start moving

protected:
    /// Specific implementation of CGhost method for Purple Ghost
    SCoordinates getTargetCoordinates(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;

public:
    /// A constructor constructs new Siena Ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CSienaGhost(const CMap &map, const SCoordinates &homeLocation);
    /// It does Siena Ghost move behaviour, overrides the basic CGhost move
    SCoordinates move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;
    /// Method implements CGhost virtual method
    SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const override;
};


#endif //PA2_2_SEMESTRALKA_CSIENAGHOST_H
