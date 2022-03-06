//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CREDGHOST_H
#define PA2_2_SEMESTRALKA_CREDGHOST_H

#include "CGhost.h"
#include "CMap.h"
#include "../SCoordinates.h"
#include "SMainEntitiesInfo.h"
#include "CGameInfo.h"

/// CRedGhost is class that represents Red Ghost
class CRedGhost : public CGhost {
protected:
    /// Specific implementation of CGhost method for Red Ghost
    SCoordinates getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;

public:
    /// A constructor constructs new Red Ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CRedGhost(const CMap & map, const SCoordinates &homeLocation);
    /// Method implements CGhost virtual method
    SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const override;
    /// Returns info in category SMainEntityInfo
    /**
     * @return pair with a bool if the entity is a main entity and if is the second return value (info in category SMainEntityInfo) valid
     * */
    pair<bool, SMainEntityInfo> getMainEntityInfo() const override;
};

#endif //PA2_2_SEMESTRALKA_CREDGHOST_H