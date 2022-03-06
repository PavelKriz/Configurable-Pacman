//
// Created by pavel on 27.04.20.
//

#include "CController.h"


void CController::doInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // quit input
            case SDL_QUIT:
                quit_ = true;
                break;
            case SDL_KEYDOWN:
                // Check the SDLKey values (keyboard)
                if(gameHandler_ != nullptr) {
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            gameHandler_->handleEvent(CGameHandler::LEFT_KEY);
                            break;
                        case SDLK_RIGHT:
                            gameHandler_->handleEvent(CGameHandler::RIGHT_KEY);
                            break;
                        case SDLK_UP:
                            gameHandler_->handleEvent(CGameHandler::UP_KEY);
                            break;
                        case SDLK_DOWN:
                            gameHandler_->handleEvent(CGameHandler::DOWN_KEY);
                            break;
                        case SDLK_RETURN:
                            gameHandler_->handleEvent(CGameHandler::ENTER_KEY);
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }
}

CController::CController() : quit_(false), view_(nullptr), gameHandler_(nullptr) { }

bool CController::loadGame(int argc, char **argv) {
    CGameLoader gameLoader;
    //try to load the files
    if( !gameLoader.loadGame(loadedGame_, argc, argv )){
        quit_ = true;
        return false;
    }
    try {
        view_ = unique_ptr<CView>(
                new CView({(int) loadedGame_.mapFields_[0].size(), (int) loadedGame_.mapFields_.size()}));
    } catch ( invalid_argument & exception) {
        cout << "Program failed." << endl;
        cout << exception.what() << endl;
        quit_ = true;
        return false;
    }

    // all loaded successfully,
    return true;
}

void CController::startGame(){
    //prepare the view
    view_->updateMap(loadedGame_.mapFields_);
    view_->updateStaticBonuses(loadedGame_.bonuses_);
    loadedGame_.player_.additionalInfo_ = EGameObjectDirection::NO_DIRECTION;
    view_->updatePlayer(loadedGame_.player_);

    uint32_t readyStartTime = SDL_GetTicks();
    // ready loop
    while(!quit_){
        doInput();
        if(readyStartTime + READY_DURATION * 1000 < SDL_GetTicks())
            break;
        view_->drawReadyScreen();
    }
}

void CController::playGame() {
    //preparation
    gameHandler_ = unique_ptr<CGameHandler>(new CGameHandler( SDL_GetTicks(), loadedGame_));

    frameStartTime_ = SDL_GetTicks();
    prevFrameTime_ = SDL_GetTicks();
    uint32_t frameTime = FRAME_DELAY;
    // game loop
    while(!quit_){
        doInput();
        gameHandler_->runGame( frameStartTime_);

        //get all the info from the handler to view
        SGameObjectInfo player;
        gameHandler_->getPlayer(player);
        view_->updatePlayer(player);

        vector<SGameObjectInfo> staticBonuses;
        gameHandler_->getStaticBonuses(staticBonuses);
        view_->updateStaticBonuses(staticBonuses);

        vector<SGameObjectInfo> ghosts;
        gameHandler_->getGhosts(ghosts);
        view_->updateGhosts(ghosts);

        SGameObjectInfo bonus;
        if(gameHandler_->getMovingBonus(bonus)){
            view_->enableMovingBonus();
            view_->updateMovingBonus(bonus);
        } else {
            view_->disableMovingBonus();
        }

        SDisplayInfo displayInfo;
        gameHandler_->getDisplayInfo(displayInfo);
        view_->updateGameDisplayInfo(displayInfo);

        //draw
        view_->draw();

        //do the time calculations
        //FPS limiting and computing frame time
        prevFrameTime_ = frameStartTime_;
        frameStartTime_ = SDL_GetTicks();
        frameTime = frameStartTime_ - prevFrameTime_;
        if(frameTime < FRAME_DELAY){
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}