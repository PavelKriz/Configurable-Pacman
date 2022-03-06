//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CCONTROLLER_H
#define PA2_2_SEMESTRALKA_CCONTROLLER_H

#include "view/CView.h"
#include "game/CGameHandler.h"
#include "CGameLoader.h"
#include <iostream>

class CController {
    bool quit_; ///< information whether quit of the application was requested
    unique_ptr<CView> view_; ///< view of the application
    unique_ptr<CGameHandler> gameHandler_; ///< game handler of the played game
    uint32_t frameStartTime_ = 0; ///< start of a current frame
    uint32_t prevFrameTime_ = 0; ///< time when has start last frame
    SLoadedGame loadedGame_; ///< game that was loaded from files

    /// Method checking input from user
    void doInput();

public:
    /// Constructs empty controller
    CController();
    /// load the game from given arguments
    /**
     * @param[in] argc number of arguments used when the game was called from terminal
     * @param[in] argv c strings with the arguments used when the game was called from terminal
     * */
    bool loadGame(int argc, char **argv);
    /// Method that starts the game
    void startGame();
    /// Method that do the play of the game
    void playGame();
};

#endif //PA2_2_SEMESTRALKA_CCONTROLLER_H