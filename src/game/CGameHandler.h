//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CGAMEHANDLER_H
#define PA2_2_SEMESTRALKA_CGAMEHANDLER_H


#include "CMap.h"
#include "CGhost.h"
#include "CPlayer.h"
#include "../SLoadedGame.h"
#include "CPickBonusCallable.h"
#include "CMovingBonus.h"
#include <ctime>


/// A class that handles the game
class CGameHandler : public CPickBonusCallable {
public:
    /// A enum that holds all the possible game inputs from player
    enum EEvent{
        UP_KEY, RIGHT_KEY, DOWN_KEY, LEFT_KEY, ENTER_KEY
    };
private:
    CMap map_; ///< The map where the game is played
    CGameInfo gameInfo_; ///< info about the current game, tightly bound with game handler
    vector<unique_ptr<CGhost>> ghosts_; ///< vector with ghosts
    unique_ptr<CMovingBonus> movingBonus_; ///< pointer to moving bonus if there is some
    unique_ptr<CPlayer> player_; ///< pointer to the player
    SLoadedGame loadedGame_; ///< game that was given to game handler in the beggining
    bool playerWasKilled_ = false; ///< information if the player was just killed
    bool playerWon_ = false; ///< information if the player has just won (won the level)

    /// Override method from CPickBonusCallable
    void pickBonus() override;
    /// Resets everything needed after one level is done
    void levelReset();
    /// Resets everything needed after player has lost
    void lostReset();
    /// Resets everything needed after player has lost life but hasn't lost the game
    void lostLifeReset();
public:
    /// It constructs new game handler (new game)
    /**
     * @param[in] time time from the start of the game
     * @param[in] loadedGame loaded game filled with map, ghosts, player, bonuses etc.
     * */
    CGameHandler(uint32_t time, const SLoadedGame &loadedGame);
    /// It represents one move of the game at a time
    /**
     * @param[in] time time from the start of the game
     * */
    EGameState runGame(uint32_t time);
    /// Handles players input to the game
    /**
     * @param[in] event event to be handled
     * */
    void handleEvent(EEvent event);
    /// Fills the info about all static bonuses in the game
    /**
     * @param[out] toFill vector that will be filled with all static (non-moving) bonuses
     * */
    void getStaticBonuses(vector<SGameObjectInfo> &toFill) const;
    /// Fills info about the player
    /**
     * @param[out] toFill structure to whitch the information about player/pacman will be saved
     * */
    void getPlayer(SGameObjectInfo &toFill) const;
    /// Fills the info about all ghosts in the game
    /**
     * @param[out] toFill vector that will be filled with all ghosts in game
     * */
    void getGhosts(vector<SGameObjectInfo> &toFill) const;
    /// Fills info about the moving bonus if there is any
    /**
     * @param[out] toFill structure to whitch the information about moving bonus will be saved if is there some moving bonus
     * @return if there is moving bonus and the information was then filled
     * */
    bool getMovingBonus(SGameObjectInfo &toFill) const;
    /// fills the display info
    /**
     * @param[out] toFill structure where the information about the game which should be displayed will be saved
     * */
    void getDisplayInfo(SDisplayInfo &toFill) const;
};


#endif //PA2_2_SEMESTRALKA_CGAMEHANDLER_H