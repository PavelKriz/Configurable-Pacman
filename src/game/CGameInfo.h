//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CGAMEINFO_H
#define PA2_2_SEMESTRALKA_CGAMEINFO_H

#include "EGameState.h"
#include "EGameMode.h"
#include "SGameParameters.h"
#include "../SDisplayInfo.h"
#include "SGameObjectInfo.h"
#include "../parameters.h"
#include "../functions.h"
#include <math.h>
#include <time.h>
#include <iostream>

/// Class that holds info about current played game
class CGameInfo {
    bool movingBonusesCanBeGenerated_ = true; ///< info if the moving bonus can be generated
    unsigned int nextMovingBonusIn_; ///< timer that determines when would be generated the next bonus
    uint32_t lastTimeMovingBonusExisted_; ///< is the last time when the moving bonus has existed
    const float baseSpeed_ = 0.03f; ///< base speed for all objects in the game
    bool movingBonusGenerated_ = false; ///< states whether moving bonus was generated
    EGameState currentState_; ///< current state of the game
    uint32_t timeOfLastChange_;  ///< time of last chang of the game state
    SGameParameters gameParameters_; ///< parameters of the game that were given in the construction of the game info
    unsigned int numberOfBonuses_; ///< number of existing static bonuses in the beginning of the game
    unsigned int numberOfPickedBonuses_ = 0; ///< number of bonuses already picked in current level
    unsigned int ghostsKilledInRow_ = 0; ///< number of ghosts killed in row
    unsigned int score_ = 0; ///< current players score
    unsigned int lives_ = NUMBER_OF_LIVES; ///< number of remaining lives
    unsigned int level_; ///< current level1
    uint32_t time_; ///< current time from the start of the game

    /// Method checks if has player already won
    void checkIfPlayerWon();
    ///  Method that cal's time to next moving bonus would be generated
    void calcTimeToMovingBonus();
    /// Calcs the neutral time length
    unsigned int calcNeutralTimeLength() const;
public:
    /// Constructs new game info to a new game
    /**
     * @param[in] time time from the start of the game
     * @param[in] gameParameters parameters of the game, which would be played
     * @param[in] numberOfBonuses number of all static (non-moving) bonuses at the start of the game
     * */
    CGameInfo( uint32_t time, SGameParameters gameParameters, unsigned int numberOfBonuses);
    /// The method by which game info is informed about collecting the bonus
    /**
     * @param[in] objectInfo information about the picked bonus
     * */
    void bonusWasPicked(const SGameObjectInfo &objectInfo);
    /// Updates timer in the game info
    /**
     * @param[in] time time from the start of the game
     * */
    void updateTime(uint32_t time);
    /// Returns info if the moving bonus should be generated. When true, then moving bonus have to be generated
    /**
     * @return if the moving bonus have to be generated
     * */
    bool generateMovingBonus();
    /// Updates current game nfo of the game by information that ghost was killed
    void ghostWasKilled();
    /// Updates current game nfo of the game by information that player was killed
    void playerWasKilled();
    /// resets the game info for a new game with the same parameters
    void reset();
    /// The method by which game info is informed about collecting the moving bonus
    void movingBonusWasPicked();
    /// Method calc's ghost speed
    /**
     * @return distance ghost can travel during one move (distance is measured as one between two tiles)
     * */
    float calcGhostSpeed() const;
    /// Method calc's player speed
    /**
     * @return distance player can travel during one move (distance is measured as one between two tiles)
     * */
    float calcPlayerSpeed() const;
    /// Method calc's moving bonus speed
    /**
     * @return distance moving bonus can travel during one move (distance is measured as one between two tiles)
     * */
    float calcMovingBonusSpeed() const;
    /// Method fills info about the game
    /**
     * @param[out] toFill structure where the information about the game which should be displayed will be saved
     * */
    void getDisplayInfo(SDisplayInfo &toFill) const;
    /// Returns  (already picked bonuses) / (bonuses on the beginning of the game)
    /**
     * @return value between 0 - 1
     * */
    float getPickedBonusesRatio() const;
    /// Returns current game state
    /**
     * @return State of the game is returned.
     * */
    EGameState getGameState() const;
    /// Returns current time in the game info
    /**
     * @return time from the start of the game
     * */
    uint32_t getTime() const;
};


#endif //PA2_2_SEMESTRALKA_CGAMEINFO_H
