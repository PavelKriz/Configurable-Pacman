//
// Created by pavel on 30.04.20.
//

#ifndef PA2_2_SEMESTRALKA_COBJECTDRAWER_H
#define PA2_2_SEMESTRALKA_COBJECTDRAWER_H

#include "../game/SGameObjectInfo.h"
#include "../parameters.h"
#include "../SSize.h"
#include "../SDisplayInfo.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

/// A class that draws all game objects and other objects
class CObjectDrawer {
    bool valid_; ///< if the CObjectDrawer is valid

    static const size_t NUMBER_OF_TEXTURES_ = 36; ///number of texture indexes
    const size_t PLAYER_RIGHT_index_ = 0; ///< texture index for game object
    const size_t PLAYER_DOWN_index_ = 1; ///< texture index for game object
    const size_t PLAYER_LEFT_index_ = 2; ///< texture index for game object
    const size_t PLAYER_UP_index_ = 3; ///< texture index for game object
    const size_t PLAYER_FRONT_index_ = 4; ///< texture index for game object
    const size_t RED_GHOST_index_ = 5; ///< texture index for game object
    const size_t TURQUOISE_GHOST_index_ = 6; ///< texture index for game object
    const size_t SIENA_GHOST_index_ = 7; ///< texture index for game object
    const size_t PURPLE_GHOST_index_ = 8; ///< texture index for game object
    const size_t MOVING_BONUS_index_ = 9; ///< texture index for game object
    const size_t BASIC_BONUS_index_ = 10; ///< texture index for game object
    const size_t KILLER_BONUS_index_ = 11; ///< texture index for game object
    const size_t WALL_index_ = 12; ///< texture index for game object
    const size_t GATE_index_ = 13; ///< texture index for game object
    const size_t EMPTY_index_ = 14; ///< texture index for game object
    const size_t SCARED_GHOST_index_ = 15; ///< texture index for game object
    const size_t KILLED_GHOST_index_ = 16; ///< texture index for game object
    const size_t WALL_CONNECTIONS_index_ = 17; ///< texture index for game object
    const size_t CORONA_index_ = 18; ///< texture index for game object
    const size_t READY_index_ = 19; ///< texture index for other info
    const size_t LEVEL_DONE_index_ = 20; ///< texture index for other info
    const size_t GAME_OVER_index_ = 21; ///< texture index for other info
    const size_t LOST_LIFE_index_ = 22; ///< texture index for other info
    const size_t LIFE_index_ = 23; ///< texture index for other info
    const size_t NUMBER_ZERO_index_ = 24; ///< texture index for number
    const size_t NUMBER_ONE_index_ = 25; ///< texture index for number
    const size_t NUMBER_TWO_index_ = 26; ///< texture index for number
    const size_t NUMBER_THREE_index_ = 27; ///< texture index for number
    const size_t NUMBER_FOUR_index_ = 28; ///< texture index for number
    const size_t NUMBER_FIVE_index_ = 29; ///< texture index for number
    const size_t NUMBER_SIX_index_ = 30; ///< texture index for number
    const size_t NUMBER_SEVEN_index_ = 31; ///< texture index for number
    const size_t NUMBER_EIGHT_index_ = 32; ///< texture index for number
    const size_t NUMBER_NINE_index_ = 33; ///< texture index for number
    const size_t SCARED_CORONA_index_ = 34; ///< texture index for number
    const size_t BOTTOM_BAR_index_ = 35; ///< texture index for other info

    ///struct holds info about texture
    struct SGameObjectTexture {
        SDL_Texture *texture_;
        SSize textureSize_;
    };

    SGameObjectTexture textures_[NUMBER_OF_TEXTURES_]; ///< game object textures and other textures

    static const unsigned int numberOfAllPossibleMapTilesTextures_ = 16; ///< number of all posible wall tiles
    SGameObjectTexture allPossibleMapTiles_[numberOfAllPossibleMapTilesTextures_];  ///< number textures

    /// Method that generates wall textures from wall and wall connections textures
    /**
     * @param[in] renderer renderer of the current application
     * */
    void generateMapTiles(SDL_Renderer *renderer);
    ///< Method that draws one map tile
    /**
     * @param[in] blit blit function that will be used for drawing the map tile
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] map imap from which the tile will be drawn
     * @param[in] x the x coordinate of the tile in the map
     * @param[in] y the y coordinate of the tile int map
     * */
    void drawMapTile(void (*blit)(SDL_Renderer *, SDL_Texture *, int, int),
                     SDL_Renderer *renderer, vector<vector<SGameObjectInfo>> &map, size_t x, size_t y);
    /// Method that draw random screen info
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the screen information
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] toDraw texture to be drawn as screen info
     * @param[in] windowSize size of the window in which is the game displayed (in pixels)
     * */
    void drawScreenInfo(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                        SGameObjectTexture & toDraw, SSize &windowSize);

public:
    /// Constructs non valid drawer
    CObjectDrawer();
    /// Destructor destructs object drawer in standard way
    ~CObjectDrawer();
    /// Method that initializes drawer and makes it valid
    /**
     * @param[in] loadTexture function that will load the SDL texture from image file
     * @param[in] renderer renderer of the current application
     * */
    void initialize(SDL_Texture *(*loadTexture)(const char *, SDL_Renderer *), SDL_Renderer *renderer);
    /// Method that draws game objects
    /**
     * @param[in] blit blit function that will be used for drawing the object
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] objectInfo information about the object that is going to be drawn
     * */
    void drawObject(void (*blit)(SDL_Renderer *renderer, SDL_Texture *, int, int), SDL_Renderer *renderer,
                    const SGameObjectInfo &objectInfo);
    /// Method that draws the game map
    /**
     * @param[in] blit blit function that will be used for drawing the map
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] map the map going to be rendered
     * */
    void drawMap(void (*blit)(SDL_Renderer *renderer, SDL_Texture *, int, int), SDL_Renderer *renderer,
                 vector<vector<SGameObjectInfo>> &map);
    /// Method that draws the bottom score map
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the bottom bar
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] displayInfo additional information about the game state
     * @param[in] mapSize size of the map of the game (in map tiles)
     * */
    void drawBottomBar(void (*sizedBlit)(SDL_Renderer *renderer, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                       SDisplayInfo &displayInfo, SSize &mapSize);
    /// Method that draws the banners (big info on the screen)
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the information banner
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] displayInfo additional information about the game state
     * @param[in] windowSize size of the window in which is the game displayed (in pixels)
     * */
    void drawBanner(void (*sizedBlit)(SDL_Renderer *renderer, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                    SDisplayInfo &displayInfo, SSize &windowSize);
    /// Method that draws the ready banner
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the ready banner
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] windowSize size of the window in which is the game displayed (in pixels)
     * */
    void drawReady(void (*sizedBlit)(SDL_Renderer *renderer, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer
            , SSize &windowSize);
    /// Method that draws the lifes of the player
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the lifes
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] displayInfo additional information about the game state
     * @param[in] windowSize size of the window in which is the game displayed (in pixels)
     * */
    void drawLifes(void (*sizedBlit)(SDL_Renderer *renderer, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer
            , SDisplayInfo &displayInfo, SSize &windowSize);
    /// Method that draws the score
    /**
     * @param[in] sizedBlit blit function that will be used for drawing the score
     * @param[in] renderer renderer that will be used for rendering
     * @param[in] displayInfo additional information about the game state
     * @param[in] windowSize size of the window in which is the game displayed (in pixels)
     * */
    void drawScore(void (*sizedBlit)(SDL_Renderer *renderer, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer
            , SDisplayInfo &displayInfo, SSize &windowSize);
};

#endif //PA2_2_SEMESTRALKA_COBJECTDRAWER_H