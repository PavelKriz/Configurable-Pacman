//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CCORONAGHOST_H
#define PA2_2_SEMESTRALKA_CCORONAGHOST_H

#include "CGhost.h"
#include "CMap.h"
#include "../SCoordinates.h"
#include "SMainEntitiesInfo.h"
#include "CGameInfo.h"

/// CCoronaGhost is class that represents special ghost that is hard to beat in the game
class CCoronaGhost : public CGhost {
protected:
    /// Specific implementation of CGhost method for Corona ghost
    SCoordinates getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) override;
public:
    /// A constructor constructs new Corona ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CCoronaGhost(const CMap & map, const SCoordinates &homeLocation);
    /// Method implements CGhost virtual method
    SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const override;
    /// Returns info in category SMainEntityInfo
    /**
     * @return pair with a bool if the entity is a main entity and if is the second return value (info in category SMainEntityInfo) valid
     * */
    pair<bool, SMainEntityInfo> getMainEntityInfo() const override;
};


#endif //PA2_2_SEMESTRALKA_CCORONAGHOST_H