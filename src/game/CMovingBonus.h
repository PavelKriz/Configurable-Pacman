//
// Created by pavel on 29.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CMOVINGBONUS_H
#define PA2_2_SEMESTRALKA_CMOVINGBONUS_H

#include "../SCoordinates.h"
#include "SGameObjectInfo.h"
#include "CMap.h"
#include "CMovingObject.h"
#include "CGameInfo.h"


/// A class representing a moving bonus
class CMovingBonus : public CMovingObject {
    unsigned int timeForOneTarget = 10; ///< time for one target of moving bonus
    uint32_t timeOfSettingTarget;  ///< time to set new target
    EDirection goingFromDirection_; ///< direction from where the object is moving from
    SCoordinates randomTile_; ///< random tile that is set as a random target

    /// Returns whether bonus can step on a map tile
    /**
     * @param[in] object the object going to be confirmed if the moving bonus can step on it
     * @return if the moving bonus can step on such a object
     * */
    static bool canStepOn(EGameObject &object);
    /// Method decides what would be the direction which would be chosen for next move
    /**
     * @param[in] map map in which the moving bonus is
     * @param[in] targetCoords are the coordinates of the target of the moving bonus
     * @return direction that is the best possible for getting to the target
     * */
    EDirection generalbonusDecision(const CMap &map, const SCoordinates & targetCoords);
    /// Returns coordinates of target, defined by specific moving bonus behaviour
    /**
     * @param[in] map map in which the moving bonus is
     * @param[in] gameInfo info which is used for game where is the moving bonus
     * @return the coordinates of the target
     * */
    SCoordinates getTargetCoordinates(const CMap & map, const CGameInfo &gameInfo);
public:
    /// Constructor constructs new moving bonus
    /**
     * @param[in] map map in which the moving bonus will be
     * @param[in] gameInfo informations about the game which will the moving bonus part of
     * */
    CMovingBonus(const CMap &map, const CGameInfo &gameInfo);
    /// It does move the moving bonus
    /**
     * @param[in] map map in which the moving bonus is
     * @param[in] gameInfo informations about the game which will the moving bonus part of
     * @return coordinates where the moving bonus currently is after the move
     * */
    virtual SCoordinates move(const CMap &map, const CGameInfo &gameInfo);
    /// Method returns basic info about the object (bonus)
    /**
     * @return the info about the game object (moving bonus)
     * */
    SGameObjectInfo getObjectInfo() const;

};

#endif //PA2_2_SEMESTRALKA_CMOVINGBONUS_H