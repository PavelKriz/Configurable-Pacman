//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_SLOADEDGAME_H
#define PA2_2_SEMESTRALKA_SLOADEDGAME_H

#include <memory>
#include <vector>
#include "game/SGameObjectInfo.h"
#include "game/CGhost.h"
#include "game/CPlayer.h"

using namespace std;

/// A structure to which is the game loaded
struct SLoadedGame {
    SGameParameters gameParameters_; ///< loaded paramters of the game
    vector<vector<SGameObjectInfo>> mapFields_; ///< game map
    vector<SGameObjectInfo> bonuses_; ///< static bonuses on the game map
    vector<SGameObjectInfo> ghosts_; ///< ghosts loaded from the map
    SGameObjectInfo player_; ///< player loaded from the map
};

#endif //PA2_2_SEMESTRALKA_SLOADEDGAME_H
