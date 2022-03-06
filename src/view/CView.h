//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CVIEW_H
#define PA2_2_SEMESTRALKA_CVIEW_H


#include "../parameters.h"
#include "../game/SGameObjectInfo.h"
#include "../SSize.h"
#include "../SDisplayInfo.h"
#include "CObjectDrawer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

using namespace std;

/// A struct that holds window and renderer
struct App{
    SDL_Renderer *renderer_; ///< sdl renderer pointer
    SDL_Window *window_; ///< sdl window pointer
};

/// A class that handle the window and graphics draw
class CView {
    App app_; ///< info about pointers on renderer and window
    CObjectDrawer objectDrawer; ///< object drawer for current view
    SSize mapSize_; ///< size of the game map
    SSize windowSize_; ///< window size in pixels
    vector<vector<SGameObjectInfo>> map_; ///< game map
    vector<SGameObjectInfo> staticBonuses_; ///< all static bonuses to display
    vector<SGameObjectInfo> ghosts_; ///< all ghosts to display
    bool movingBonusEnabled_ = false; ///< information whether display moving bonus
    SGameObjectInfo movingBonus_; ///< moving bonus
    SGameObjectInfo player_; ///< player/pacman
    SDisplayInfo displayInfo_; ///< display info about the game

    /// Method initializing SDL (window, renderer...)
    void initSDL();
    /// preparing scene for drawing
    void prepareScene();
    /// change display buffers and get the render
    void presentScene();
    /// Method that loads texture and throws invalid argument if texture wasnt loaded
    static SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
    /// move texture to rendered buffer on given coordinates
    static void blit(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
    /// move texture of given size to rendered buffer on given coordinates
    static void sizedBlit(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

public:
    /// constructs valid cviw with window already opened
    /**
     * @param[in] mapSize size of the map that will be used in the game (size is in tiles)
     * */
    CView(const SSize &mapSize);
    /// destructs the view and its parts
    ~CView();
    /// method that draws the game
    void draw();
    /// method that draws the ready screen for the game
    void drawReadyScreen();
    /// Method updating game display info
    /**
     * @param[in] displayInfo display information in the view will be updated by this one
     * */
    void updateGameDisplayInfo(const SDisplayInfo &displayInfo);
    /// Method for updating map
    /**
     * @param[in] map map information in the view will be update by this one
     * */
    void updateMap(const vector<vector<SGameObjectInfo>> &map);
    /// Method for updating ghosts
    /**
     * @param[in] ghosts information about ghosts in the view will be update by these ones
     * */
    void updateGhosts(const vector<SGameObjectInfo> &ghosts);
    /// Method for updating static bonuses
    /**
     * @param[in] staticBonuses information about static (non-moving) bonuses in the view will be update by these ones
     * */
    void updateStaticBonuses(const vector<SGameObjectInfo> &staticBonuses);
    /// Method for updating moving bonus
    /**
     * @param[in] movingBonus moving bonus informationin the view will be update by this one
     * */
    void updateMovingBonus(const SGameObjectInfo &movingBonus);
    /// Method for updating player
    /**
     * @param[in] movingBonus player information in the view will be update by this one
     * */
    void updatePlayer(const SGameObjectInfo &player);
    /// turn on drawing of the moving bonus
    void enableMovingBonus();
    /// turn off drawing of the moving bonus
    void disableMovingBonus();
};

#endif //PA2_2_SEMESTRALKA_CVIEW_H