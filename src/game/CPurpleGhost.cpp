//
// Created by pavel on 27.04.20.
//

#include "CPurpleGhost.h"


SCoordinates CPurpleGhost::getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    SCoordinates moveVector;
    switch (gameInfo.getGameState()) {
        case GAMESTATE_HUNT_ON_PLAYER:
            randomTileSet_ = false;
            moveVector = getMoveVector(mainEntitiesInfo.playerInfo_.direction_, (float) inFront);
            return map.getMapCoordinates(mainEntitiesInfo.playerInfo_.coordinates_).tryMove(moveVector);
        case GAMESTATE_NEUTRAL:
            randomTileSet_ = false;
            return {0,(float) (map.mapSize().y_ - 1)};
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
        default: //case GAMESTATE_LOST_LIFE:
            return mainEntitiesInfo.playerInfo_.coordinates_;
    }
}

CPurpleGhost::CPurpleGhost(const CMap &map, const SCoordinates &homeLocation) : CGhost(map, homeLocation) {

}

SCoordinates CPurpleGhost::move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    if(!began){
        if(gameInfo.getPickedBonusesRatio() > beganTreshold ){
            began = true;
        } else {
            return location_.get();
        }
    }
    return CGhost::move(map, mainEntitiesInfo,gameInfo);
}

SGameObjectInfo CPurpleGhost::getObjectInfo( const CGameInfo &gameInfo) const {
    if(!alive_){
        return {location_.get(), GAMEOBJECT_KILLED_GHOST};
    }
    if(gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
        return {location_.get(), GAMEOBJECT_SCARED_GHOST};
    } else {
        return {location_.get(), GAMEOBJECT_PURPLE_GHOST};
    }
}
