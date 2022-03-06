//
// Created by pavel on 27.04.20.
//

#include "CSienaGhost.h"


SCoordinates CSienaGhost::getTargetCoordinates(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    float distFromPlayer;
    switch (gameInfo.getGameState()) {
        case GAMESTATE_HUNT_ON_PLAYER:
            randomTileSet_ = false;
            distFromPlayer = calcDistance(mainEntitiesInfo.playerInfo_.coordinates_, location_.get());
            if(distFromPlayer < 8){
                return {0,0};
            } else {
                return mainEntitiesInfo.playerInfo_.coordinates_;
            }
        case GAMESTATE_NEUTRAL:
            randomTileSet_ = false;
            return {(float) (map.mapSize().x_ - 1), (float) (map.mapSize().y_ - 1)};
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
            return location_.get();
        default: // case GAMESTATE_LOST_LIFE
            return mainEntitiesInfo.playerInfo_.coordinates_;
    }
}

CSienaGhost::CSienaGhost(const CMap &map, const SCoordinates &homeLocation) : CGhost(map, homeLocation) {

}

SCoordinates CSienaGhost::move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    if(!began){
        if(gameInfo.getPickedBonusesRatio() > beganTreshold ){
            began = true;
        } else {
            return location_.get();
        }
    }
    return CGhost::move(map, mainEntitiesInfo,gameInfo);
}

SGameObjectInfo CSienaGhost::getObjectInfo(const CGameInfo &gameInfo) const {
    if(!alive_){
        return {location_.get(), GAMEOBJECT_KILLED_GHOST};
    }
    if(gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
        return {location_.get(), GAMEOBJECT_SCARED_GHOST};
    } else {
        return {location_.get(), GAMEOBJECT_SIENA_GHOST};
    }
}
