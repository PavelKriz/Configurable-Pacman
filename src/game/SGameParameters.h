//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_SGAMEPARAMETERS_H
#define PA2_2_SEMESTRALKA_SGAMEPARAMETERS_H

#include "EGameMode.h"
#include "EGameState.h"

/// Game parameters are all the parameters loaded from config file
struct SGameParameters {
    EGameMode gameMode_; ///< game mode
    float ghostSpeedCoeficient_; ///< ghost speed coeficient
    int neutralTimeLength_; ///< neutral game time length
    unsigned int huntOnGhostsTimeLength_; ///< hunt on ghosts time length
    unsigned int huntOnPlayerTimeLength_; ///< hunt on player time length
    unsigned int probabilityOfMovingBonus_; ///< time of the moving bonus to generate
};

#endif //PA2_2_SEMESTRALKA_SGAMEPARAMETERS_H
