//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CGHOST_H
#define PA2_2_SEMESTRALKA_CGHOST_H

#include "../SCoordinates.h"
#include "CGameInfo.h"
#include "SGameObjectInfo.h"
#include "CMap.h"
#include "CMovingObject.h"
#include "SMainEntitiesInfo.h"
#include <limits>


/// A class that represents ghost in the game, it solves common problems of all ghosts in its methods
class CGhost : public CMovingObject {
protected:
    SCoordinates homeLocation_; ///< home location of the ghost
    uint32_t timeOfDeath_ = 0; ///< time when the ghost was killed
    bool alive_; ///< information if is the ghost alive
    bool randomTileSet_; ///< information if a new random tile was set
    SCoordinates randomTile_; ///< random tile is there for random target of the ghost
    EDirection goingFromDirection_; ///< holds the direction from which is the ghost going

    /// Decides what would be the direction which would be chosen for next move
    /**
     * @param[in] map map in which the ghost is
     * @param[in] targetCoords are the coordinates of the target of the ghost
     * @return direction that is the best possible for getting to the target
     * */
    EDirection generalGhostDecision(const CMap &map, const SCoordinates & targetCoords);
    /// Decides if ghost can step on given map object
    /**
     * @param[in] object the object going to be confirmed if the ghost can step on it
     * @return if the ghost can step on such a object
     * */
    static bool canStepOn(EGameObject &object);
    /// Returns coordinates of target, defined by specific ghost behaviour
    /**
     * @param[in] map map in which the ghost is
     * @param[in] mainEntitiesInfo information about main entities in the game
     * @param[in] gameInfo info which is used for game where is actual ghost
     * @return the coordinates of the target
     * */
    virtual SCoordinates getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo,
            const CGameInfo &gameInfo) = 0;
public:
    /// It initializes new ghost
    /**
     * @param[in] map map in which the ghost will be
     * @param[in] homeLocation start and home location for the ghost
     * */
    CGhost(const CMap &map, const SCoordinates &homeLocation);
    /// It does general CGhost move behaviour
    /**
     * @param[in] map map in which the ghost is
     * @param[in] mainEntitiesInfo information about main entities in the game
     * @param[in] time time from start of the game
     * @return coordinates where the ghost currently is after the move
     * */
    virtual SCoordinates move(const CMap &map, const SMainEntitiesInfo & mainEntitiesInfo, const CGameInfo &gameInfo);
    /// Method for resetting the ghost to the beginning state
    /**
     * @param[in] map map in which the ghost is
     * */
    void reset(const CMap &map);
    /// The method by which ghost is informed about his death
    /**
     * @param[in] map map in which the ghost is
     * @param[in] time time from start of the game
     * */
    void killed(const CMap &map, uint32_t time);
    /// Returns information whether the ghost can kill player
    /**
     * @param[in] gameInfo info is needed for deciding if ghost can kill
     * @return if can kill
     * */
    bool canKill(const CGameInfo &gameInfo) const;
    /// Returns information whether the ghost can be killed
    /**
     * @param[in] gameInfo info is needed for deciding if ghost can be killed
     * @return if can be killed
     * */
    bool canBeKilled(const CGameInfo &gameInfo) const;
    /// Returns basic info about the ghost
    /**
     * @param[in] gameInfo info which is used for game where is actual ghost
     * @return the info about the game object (ghost)
     * */
    virtual SGameObjectInfo getObjectInfo(const CGameInfo &gameInfo) const = 0;
    /// Returns info in category SMainEntityInfo
    /**
     * @return pair with a bool if the entity is a main entity and if is the second return value (info in category SMainEntityInfo) valid
     * */
    virtual pair<bool, SMainEntityInfo> getMainEntityInfo() const;
};

#endif //PA2_2_SEMESTRALKA_CGHOST_H