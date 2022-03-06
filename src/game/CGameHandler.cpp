//

#include "CGameHandler.h"
#include "CRedGhost.h"
#include "CPurpleGhost.h"
#include "CTurquoiseGhost.h"
#include "CSienaGhost.h"
#include "CCoronaGhost.h"

//
// Created by pavel on 27.04.20.

void CGameHandler::pickBonus() {
    pair<bool,SGameObjectInfo> bonus;
    if(player_->isOnIntersection()){
        SGameObjectInfo info = player_->getObjectInfo();
        bonus = map_.pickBonus(info.location_);
        if(bonus.first){
            gameInfo_.bonusWasPicked(bonus.second);
        }
    }
}

void CGameHandler::levelReset() {
    for(const auto &it: ghosts_)
        it->reset(map_);
    player_->reset(map_);
    map_.reset();
    playerWon_ = false;
    playerWasKilled_ = false;
    movingBonus_ = unique_ptr<CMovingBonus>(nullptr);
    gameInfo_.movingBonusWasPicked();
}

void CGameHandler::lostReset() {
    for(const auto &it: ghosts_)
        it->reset(map_);
    player_->reset(map_);
    map_.reset();
    gameInfo_.reset();
    playerWon_ = false;
    playerWasKilled_ = false;
}

void CGameHandler::lostLifeReset() {
    for(const auto &it: ghosts_)
        it->reset(map_);
    player_->reset(map_);
    playerWon_ = false;
    playerWasKilled_ = false;
}

CGameHandler::CGameHandler(uint32_t time, const SLoadedGame &loadedGame)
:
map_(loadedGame.mapFields_, loadedGame.bonuses_),
gameInfo_( time,loadedGame.gameParameters_, loadedGame.bonuses_.size()),
player_(nullptr),
loadedGame_(loadedGame)
{
    player_ = unique_ptr<CPlayer>( new CPlayer( map_, loadedGame.player_.location_));
    // generate ghosts based on current game mode
    if(loadedGame.gameParameters_.gameMode_ == GAMEMODE_HARD){
        for (size_t i = 0; i < loadedGame.ghosts_.size(); ++i) {
            ghosts_.push_back(unique_ptr<CGhost>(new CCoronaGhost(map_, loadedGame.ghosts_[i].location_)));
        }
    } else if (loadedGame.gameParameters_.gameMode_ == GAMEMODE_NORMAL){
        for (size_t i = 0; i < loadedGame.ghosts_.size(); ++i) {
            switch (i % 4) {
                case 0:
                    ghosts_.push_back(unique_ptr<CGhost>(new CRedGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 1:
                    ghosts_.push_back(unique_ptr<CGhost>(new CPurpleGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 2:
                    ghosts_.push_back(unique_ptr<CGhost>(new CTurquoiseGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 3:
                    ghosts_.push_back(unique_ptr<CGhost>(new CSienaGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
            }
        }
    } else {
        // GAMEMODE random
        srand(time);
        for (size_t i = 0; i < loadedGame.ghosts_.size(); ++i) {
            int randomNumber = rand() % 4;
            switch ( randomNumber ) {
                case 0:
                    ghosts_.push_back(unique_ptr<CGhost>(new CRedGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 1:
                    ghosts_.push_back(unique_ptr<CGhost>(new CPurpleGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 2:
                    ghosts_.push_back(unique_ptr<CGhost>(new CTurquoiseGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
                case 3:
                    ghosts_.push_back(unique_ptr<CGhost>(new CSienaGhost(map_, loadedGame.ghosts_[i].location_)));
                    break;
            }
        }
    }
}

EGameState CGameHandler::runGame(uint32_t time) {
    // three phases of the game
    //FIRST PHASE - check game states and other, prepare for second phase
    gameInfo_.updateTime(time);

    EGameState currentState = gameInfo_.getGameState();
    if(playerWasKilled_){
        if(currentState!= GAMESTATE_LOST_LIFE){
            lostLifeReset();
        }
    }

    if(playerWon_){
        if(currentState != GAMESTATE_VICTORY){
            levelReset();
        }
    } else {
        if(currentState == GAMESTATE_VICTORY){
            playerWon_ = true;
        }
    }

    if(currentState == GAMESTATE_LOST || currentState == GAMESTATE_VICTORY){
        return currentState;
    }

    if(gameInfo_.generateMovingBonus()){
        movingBonus_ = unique_ptr<CMovingBonus>(new CMovingBonus(map_, gameInfo_));
    }

    //SECOND PHASE - move all movable objects
    SCoordinates playersCoords;
    SMainEntitiesInfo mainEntitiesInfo;
    playersCoords = player_->move(map_, gameInfo_, this);
    mainEntitiesInfo.playerInfo_ = player_->getMainEntityInfo();

    if(movingBonus_.get() != nullptr){
        movingBonus_->move(map_, gameInfo_);
    }

    for(const auto& it: ghosts_) {
        pair<bool, SMainEntityInfo> mainGhostpossibly;
        if((mainGhostpossibly = it->getMainEntityInfo()).first)
            mainEntitiesInfo.mainGhostInfo_ = mainGhostpossibly.second;
    }

    for(const auto& it: ghosts_){
        it->move(map_, mainEntitiesInfo, gameInfo_);
    }

    //THIRD PHASE check collisions
    //check collisions of player with ghosts
    for(auto &it: ghosts_){
        if(gameInfo_.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
            SGameObjectInfo test = it->getObjectInfo(gameInfo_);
            if(areFloatsEqual(test.location_.x_, playersCoords.x_, KILL_DISTANCE) &&
            (areFloatsEqual(test.location_.y_, playersCoords.y_, KILL_DISTANCE))){
                if(it->canBeKilled(gameInfo_)) {
                    it->killed(map_, time);
                    gameInfo_.ghostWasKilled();
                }
            }
        } else if(gameInfo_.getGameState() == GAMESTATE_HUNT_ON_PLAYER || gameInfo_.getGameState() == GAMESTATE_NEUTRAL){
            SGameObjectInfo test = it->getObjectInfo(gameInfo_);
            if(areFloatsEqual(test.location_.x_, playersCoords.x_, KILL_DISTANCE) &&
               (areFloatsEqual(test.location_.y_, playersCoords.y_, KILL_DISTANCE))){
                if(it->canKill(gameInfo_)) {
                    player_->killed();
                    playerWasKilled_ = true;
                    gameInfo_.playerWasKilled();
                }
            }
        }
    }
    //check collisions of player with moving bonus
    if(movingBonus_.get() != nullptr){
        if(areFloatsEqual(movingBonus_->getObjectInfo().location_.x_, playersCoords.x_, KILL_DISTANCE) &&
           (areFloatsEqual(movingBonus_->getObjectInfo().location_.y_, playersCoords.y_, KILL_DISTANCE))){
            gameInfo_.bonusWasPicked(movingBonus_->getObjectInfo());
            movingBonus_ = unique_ptr<CMovingBonus>(nullptr);
        }
    }

    return gameInfo_.getGameState();
}

void CGameHandler::handleEvent(CGameHandler::EEvent event) {
    switch (event) {
        case UP_KEY:
            player_->changeDirection(CMovingObject::DIRECTION_UP);
            break;
        case RIGHT_KEY:
            player_->changeDirection(CMovingObject::DIRECTION_RIGHT);
            break;
        case DOWN_KEY:
            player_->changeDirection(CMovingObject::DIRECTION_DOWN);
            break;
        case LEFT_KEY:
            player_->changeDirection(CMovingObject::DIRECTION_LEFT);
            break;
        case ENTER_KEY:
            if(gameInfo_.getGameState() == GAMESTATE_LOST){
                lostReset();
            }
            break;
    }
}

void CGameHandler::getStaticBonuses(vector<SGameObjectInfo> &toFill) const {
    map_.getStaticBonuses(toFill);
}

void CGameHandler::getPlayer(SGameObjectInfo &toFill) const {
    toFill = player_->getObjectInfo();
}

void CGameHandler::getGhosts(vector<SGameObjectInfo> &toFill) const {
    for(const auto & it: ghosts_){
        toFill.push_back(it->getObjectInfo(gameInfo_));
    }
}

bool CGameHandler::getMovingBonus(SGameObjectInfo &toFill) const {
    if(movingBonus_.get() != nullptr){
        toFill = movingBonus_->getObjectInfo();
        return true;
    }
    return false;
}

void CGameHandler::getDisplayInfo(SDisplayInfo &toFill) const {
    gameInfo_.getDisplayInfo(toFill);
}