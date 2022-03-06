//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CPLAYER_H
#define PA2_2_SEMESTRALKA_CPLAYER_H

#include "../SCoordinates.h"
#include "CMap.h"
#include "CMovingObject.h"
#include "CGameInfo.h"
#include "CPickBonusCallable.h"
#include "SMainEntitiesInfo.h"


using namespace std;

/// Class that represents player/Pacman
class CPlayer : public CMovingObject {
private:
    SCoordinates homeCoordinates_; ///< coordinates of Pacman's home
    EDirection currentDirection_;  ///< current direction of Pacman
    EDirection nextDirection_; ///< next direction that was get from the player input
    bool alive_; ///< if is the player alive

    /// Method updates current direction by next direction
    void updateDirection(const CMap &map);
public:
    /// Construct new player
    /**
     * @param[in] map map in which the player will be
     * @param[in] coordinates start and home location for the player
     * */
    CPlayer(const CMap &map, const SCoordinates &coordinates);
    /// Method handles user input
    /**
     * @param[in] direction new desired direction of movement
     * */
    void changeDirection(EDirection direction);
    /// Method moves the player on the wished direction if its possible
    /**
     * @param[in] map map in which the player is
     * @param[in] gameInfo information about the game in which the player is
     * @param[in] pickBonusCallable interface for calling check if some bonus was picked
     * @return coordinates where the player currently is after the move
     * */
    SCoordinates move(const CMap &map, const CGameInfo &gameInfo, CPickBonusCallable *pickBonusCallable);
    /// The method by which class is informed about its death
    void killed();
    /// resets the player to beginning state
    /**
     * @param[in] map map in which the player is
     * */
    void reset(const CMap &map);
    /// Returns info in category SMainEntityInfo
    /**
     * @return information about player in category SMainEntityInfo
     * */
    SMainEntityInfo getMainEntityInfo() const;
    /// Returns basic info about the player
    /**
     * @return basic info about the player
     * */
    SGameObjectInfo getObjectInfo() const;
};


#endif //PA2_2_SEMESTRALKA_CPLAYER_H
