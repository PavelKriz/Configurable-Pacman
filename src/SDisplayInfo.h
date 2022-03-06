//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_SDISPLAYINFO_H
#define PA2_2_SEMESTRALKA_SDISPLAYINFO_H

#include "game/EGameState.h"
#include "game/EGameMode.h"

/// A structure holds important informations for view
struct SDisplayInfo {
    unsigned int level_; ///< current level
    unsigned int lives_; ///< current amount of players lives
    EGameState gameState_; ///< current game state
    EGameMode gameMode_; ///< current game mode
    unsigned int score_; ///< current score
    unsigned int bonusesPicked_; ///< current amount of picked bonuses in this level
    unsigned int possibleBonusesToPick_; ///< possible amount of bonuses that can be picked
};

#endif //PA2_2_SEMESTRALKA_SDISPLAYINFO_H
