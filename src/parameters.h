//
// Created by pavel on 30.04.20.
//

#ifndef PA2_2_SEMESTRALKA_PARAMETERS_H
#define PA2_2_SEMESTRALKA_PARAMETERS_H

const unsigned int BASIC_BONUS_VALUE = 50; ///< score value of basic bonus
const unsigned int KILLER_BONUS_VALUE = 200; ///< base score value of killing a ghost
const unsigned int MOVING_BONUS_VALUE = 500; ///< score value of moving bonus
const unsigned int LEVEL_DONE_VALUE = 1000; ///< score value for finishing level
const float KILL_DISTANCE = 0.5f; ///< on that distance can one object kill another
const unsigned int LOST_LIFE_DURATION = 2; ///< length of pause after player lost one live
const unsigned int WIN_DURATION = 2; ///< length of pause after player has won one level
const unsigned int NUMBER_OF_LIVES = 3; ///< number of player's lives
const unsigned int LENGTH_OF_GHOST_DEATH = 5; ///< length of pause of ghost's move after ghost was killed
const float SCARED_GHOST_SPEED_COEFICIENT = 0.5f; ///< how much slower or faster would be the scared ghosts
const float BANNER_RATIO = 0.7f; ///< scale values for info banners (0.1 - 1 would be ok)

const unsigned int STANDARD_TILE_SIZE = 40; ///< size of normal texture square - not educated changes made on this parameter would brake the game view
const unsigned int TILE_SIZE = 40;  ///< desired size of a tile in pixels - may be changed to change the size of the screen
const unsigned int BOTTOM_BAR_SIZE = 40; ///< size of the bottom bar size in pixels

const char *const WINDOW_NAME_ = "PA2 - Pacman"; ///< Application window name

const char *const BOTTOM_SCORE_BAR_TEXTURE_FILENAME = "images/scoreBar.png"; ///< path to the texture

const char *const GAMEOBJECT_PLAYER_RIGHT_TEXTURE_FILENAME = "images/pacman/pacmanRight.png"; ///< path to the texture
const char *const GAMEOBJECT_PLAYER_DOWN_TEXTURE_FILENAME = "images/pacman/pacmanDown.png"; ///< path to the texture
const char *const GAMEOBJECT_PLAYER_LEFT_TEXTURE_FILENAME = "images/pacman/pacmanLeft.png"; ///< path to the texture
const char *const GAMEOBJECT_PLAYER_UP_TEXTURE_FILENAME = "images/pacman/pacmanUp.png"; ///< path to the texture
const char *const GAMEOBJECT_PLAYER_FRONT_TEXTURE_FILENAME = "images/pacman/pacmanFront.png"; ///< path to the texture
const char *const GAMEOBJECT_RED_GHOST_TEXTURE_FILENAME = "images/redGhost.png"; ///< path to the texture
const char *const GAMEOBJECT_TURQUOISE_GHOST_TEXTURE_FILENAME = "images/turquoiseGhost.png"; ///< path to the texture
const char *const GAMEOBJECT_SIENA_GHOST_TEXTURE_FILENAME = "images/sienaGhost.png"; ///< path to the texture
const char *const GAMEOBJECT_PURPLE_GHOST_TEXTURE_FILENAME = "images/purpleGhost.png"; ///< path to the texture
const char *const GAMEOBJECT_MOVING_BONUS_TEXTURE_FILENAME = "images/movingBonus.png"; ///< path to the texture
const char *const GAMEOBJECT_BASIC_BONUS_TEXTURE_FILENAME = "images/basicBonus.png"; ///< path to the texture
const char *const GAMEOBJECT_KILLER_BONUS_TEXTURE_FILENAME = "images/killerBonus.png"; ///< path to the texture
const char *const GAMEOBJECT_WALL_TEXTURE_FILENAME = "images/wall.png"; ///< path to the texture
const char *const GAMEOBJECT_GATE_TEXTURE_FILENAME = "images/gate.png"; ///< path to the texture
const char *const GAMEOBJECT_EMPTY_TEXTURE_FILENAME = "images/tile.png"; ///< path to the texture
const char *const GAMEOBJECT_KILLED_GHOST_TEXTURE_FILENAME = "images/killedGhost.png"; ///< path to the texture
const char *const GAMEOBJECT_SCARED_GHOST_TEXTURE_FILENAME = "images/scaredGhost.png"; ///< path to the texture
const char *const WALL_CONNECTIONS_TEXTURE_FILENAME = "images/wallConnections.png"; ///< path to the texture
const char *const GAMEOBJECT_CORONA_TEXTURE = "images/corona.png"; ///< path to the texture
const char *const GAMEOBJECT_SCARED_CORONA_TEXTURE = "images/scaredCorona.png"; ///< path to the texture
const char *const BANNER_READY_TEXTURE = "images/ready.png"; ///< path to the texture

const char *const BANNER_LEVEL_DONE_TEXTURE = "images/levelDone.png"; ///< path to the texture
const char *const BANNER_GAME_OVER_TEXTURE = "images/gameOver.png"; ///< path to the texture
const char *const BANNER_LOST_LIFE_TEXTURE = "images/lostLife.png"; ///< path to the texture
const char *const LIFE_TEXTURE = "images/life.png"; ///< path to the texture

const char *const NUMBER_ZERO_TEXTURE = "images/numbers/zero.png"; ///< path to the texture
const char *const NUMBER_ONE_TEXTURE = "images/numbers/one.png"; ///< path to the texture
const char *const NUMBER_TWO_TEXTURE = "images/numbers/two.png"; ///< path to the texture
const char *const NUMBER_THRE_TEXTURE = "images/numbers/three.png"; ///< path to the texture
const char *const NUMBER_FOUR_TEXTURE = "images/numbers/four.png"; ///< path to the texture
const char *const NUMBER_FIVE_TEXTURE = "images/numbers/five.png"; ///< path to the texture
const char *const NUMBER_SIX_TEXTURE = "images/numbers/six.png"; ///< path to the texture
const char *const NUMBER_SEVEN_TEXTURE = "images/numbers/seven.png"; ///< path to the texture
const char *const NUMBER_EIGHT_TEXTURE = "images/numbers/eight.png"; ///< path to the texture
const char *const NUMBER_NINE_TEXTURE = "images/numbers/nine.png"; ///< path to the texture

const int GAMEMODE_NORMAL_INDEX = 0; ///< normal game mode index, cant be same as other indexes
const int GAMEMODE_HARD_INDEX = 1; ///< hard game mode index, cant be same as other indexes
const int GAMEMODE_RANDOM_INDEX = 2; ///< random game mode index, cant be same as other indexes

const unsigned int READY_DURATION = 3; ///< duration of the ready screen

const unsigned int MAX_FPS = 60; ///< fps limiter, changes would change the speed of the game
const unsigned int FRAME_DELAY = 1000 / MAX_FPS; ///< ideal deleay between frames, do not change

#endif //PA2_2_SEMESTRALKA_PARAMETERS_H