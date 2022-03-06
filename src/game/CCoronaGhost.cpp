//
// Created by pavel on 09.06.20.
//

#include "CCoronaGhost.h"


SCoordinates CCoronaGhost::getTargetCoordinates(const CMap & map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    //decide which coordinates to return based on game state
    switch (gameInfo.getGameState()) {
        case GAMESTATE_HUNT_ON_PLAYER:
            randomTileSet_ = false;
            return mainEntitiesInfo.playerInfo_.coordinates_;
        case GAMESTATE_NEUTRAL:
            if(!randomTileSet_){
                randomTileSet_ = true;
                randomTile_ = map.getRandomTile();
            }
            return randomTile_;
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
        case GAMESTATE_LOST_LIFE:
            return mainEntitiesInfo.playerInfo_.coordinates_;
    }
    return mainEntitiesInfo.playerInfo_.coordinates_;
}

CCoronaGhost::CCoronaGhost(const CMap &map, const SCoordinates &homeLocation) : CGhost(map, homeLocation) {}

SGameObjectInfo CCoronaGhost::getObjectInfo(const CGameInfo &gameInfo) const{
    if(!alive_){
        return {location_.get(), GAMEOBJECT_KILLED_GHOST};
    }
    if(gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS){
        return {location_.get(), GAMEOBJECT_SCARED_CORONA};
    } else {
        return {location_.get(), GAMEOBJECT_CORONA_GHOST};
    }
}

pair<bool, SMainEntityInfo> CCoronaGhost::getMainEntityInfo() const {
    return make_pair<bool, SMainEntityInfo>(true, {getOpositeDirectionTo(goingFromDirection_), location_.get()});
}