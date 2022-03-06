//
// Created by pavel on 27.04.20.
//

#include "CRedGhost.h"


SCoordinates CRedGhost::getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    switch (gameInfo.getGameState()) {
        case GAMESTATE_HUNT_ON_PLAYER:
            randomTileSet_ = false;
            return mainEntitiesInfo.playerInfo_.coordinates_;
        case GAMESTATE_NEUTRAL:
            randomTileSet_ = false;
            return {0,0};
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

CRedGhost::CRedGhost(const CMap &map, const SCoordinates &homeLocation) : CGhost(map, homeLocation) {

}

SGameObjectInfo CRedGhost::getObjectInfo(const CGameInfo &gameInfo) const {
    if(!alive_){
        return {location_.get(), GAMEOBJECT_KILLED_GHOST};
    }
    if(gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
        return {location_.get(), GAMEOBJECT_SCARED_GHOST};
    } else {
        return {location_.get(), GAMEOBJECT_RED_GHOST};
    }
}

pair<bool, SMainEntityInfo> CRedGhost::getMainEntityInfo() const {
    return make_pair<bool, SMainEntityInfo>(true, {getOpositeDirectionTo(goingFromDirection_), location_.get()});
}