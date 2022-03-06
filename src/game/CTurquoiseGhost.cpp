//
// Created by pavel on 27.04.20.
//

#include "CTurquoiseGhost.h"


SCoordinates CTurquoiseGhost::getTargetCoordinates(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    SCoordinates moveVector;
    SCoordinates pointInFrontOfPlayer;
    float x,y;
    switch (gameInfo.getGameState()) {
        case GAMESTATE_HUNT_ON_PLAYER:
            randomTileSet_ = false;
            moveVector = getMoveVector(mainEntitiesInfo.playerInfo_.direction_, inFront);
            pointInFrontOfPlayer =  map.getMapCoordinates(mainEntitiesInfo.playerInfo_.coordinates_).tryMove(moveVector);
            x = 2 * (pointInFrontOfPlayer.x_ - mainEntitiesInfo.mainGhostInfo_.coordinates_.x_);
            y = 2 * (pointInFrontOfPlayer.y_ - mainEntitiesInfo.mainGhostInfo_.coordinates_.y_);
            return location_.tryMove({ x, y});
        case GAMESTATE_NEUTRAL:
            randomTileSet_ = false;
            return {(float) (map.mapSize().x_ - 1), 0};
        case GAMESTATE_HUNT_ON_GHOSTS:
            if(!randomTileSet_){
                randomTileSet_ = true;
                randomTile_ = map.getRandomTile();
            }
            return randomTile_;
        case GAMESTATE_VICTORY:
            randomTileSet_ = false;
            return location_.get();
        case GAMESTATE_LOST:
            randomTileSet_ = false;
            return  location_.get();
        default: //case GAMESTATE_LOST_LIFE:
            return mainEntitiesInfo.playerInfo_.coordinates_;
    }
}

CTurquoiseGhost::CTurquoiseGhost(const CMap &map, const SCoordinates &homeLocation) : CGhost(map, homeLocation) {

}

SCoordinates
CTurquoiseGhost::move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    if(!began){
        if(gameInfo.getPickedBonusesRatio() > beganTreshold ){
            began = true;
        } else {
            return location_.get();
        }
    }
    return CGhost::move(map, mainEntitiesInfo,gameInfo);
}

SGameObjectInfo CTurquoiseGhost::getObjectInfo(const CGameInfo &gameInfo) const {
    if(!alive_){
        return {location_.get(), GAMEOBJECT_KILLED_GHOST};
    }
    if(gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
        return {location_.get(), GAMEOBJECT_SCARED_GHOST};
    } else {
        return {location_.get(), GAMEOBJECT_TURQUOISE_GHOST};
    }
}
