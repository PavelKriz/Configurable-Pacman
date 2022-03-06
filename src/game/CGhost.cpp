//
// Created by pavel on 27.04.20.
//

#include "CGhost.h"


CMovingObject::EDirection CGhost::generalGhostDecision(const CMap &map, const SCoordinates &targetCoords) {
    //Finding the closest neighbour field to the target
    float minDistance = numeric_limits<float>::max();
    EDirection retDir = NO_DIRECTION;
    if (goingFromDirection_ != DIRECTION_RIGHT) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_RIGHT);
        if (canStepOn(inDirection)) {
            float dist = calcDistance(targetCoords, location_.tryMove({1, 0}));
            if (dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_RIGHT;
            }
        }
    }

    if (goingFromDirection_ != DIRECTION_DOWN) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_DOWN);
        if (canStepOn(inDirection)) {
            float dist = calcDistance(targetCoords, location_.tryMove({0, 1}));
            if (dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_DOWN;
            }
        }
    }
    if (goingFromDirection_ != DIRECTION_LEFT) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_LEFT);
        if (canStepOn(inDirection)) {
            float dist = calcDistance(targetCoords, location_.tryMove({-1, 0}));
            if (dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_LEFT;
            }
        }
    }
    if (goingFromDirection_ != DIRECTION_UP) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_UP);
        if (canStepOn(inDirection)) {
            float dist = calcDistance(targetCoords, location_.tryMove({0, -1}));
            if (dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_UP;
            }
        }
    }

    if (retDir == NO_DIRECTION) {
        retDir = goingFromDirection_;
    }

    return retDir;
}

bool CGhost::canStepOn(EGameObject &object) {
    if (object != GAMEOBJECT_WALL)
        return true;
    return false;
}

CGhost::CGhost(const CMap &map, const SCoordinates &homeLocation)
        :
        CMovingObject(map, homeLocation),
        homeLocation_(homeLocation),
        alive_(true),
        randomTileSet_(false),
        goingFromDirection_(NO_DIRECTION) {
}

SCoordinates CGhost::move(const CMap &map, const SMainEntitiesInfo &mainEntitiesInfo, const CGameInfo &gameInfo) {
    //finding out if the ghost can move
    if (!alive_) {
        if (gameInfo.getTime() > timeOfDeath_ + 1000 * LENGTH_OF_GHOST_DEATH) {
            alive_ = true;
        } else {
            return location_.get();
        }
    }

    float ghostSpeed = gameInfo.calcGhostSpeed();
    EDirection dir = getOpositeDirectionTo(goingFromDirection_);

    //move while there is a still some distance for moving
    while (!areFloatsEqual(ghostSpeed, 0)) {
        if (isOnIntersection()) {
            dir = generalGhostDecision(map, getTargetCoordinates(map, mainEntitiesInfo, gameInfo));
            goingFromDirection_ = getOpositeDirectionTo(dir);
        }

        if (goingFromDirection_ == NO_DIRECTION) {
            return {location_.x(), location_.y()};
        }

        SCoordinates moveVector = getMoveVector(dir, ghostSpeed);
        ghostSpeed = innerGridMove(moveVector);
    }

    return location_.get();
}

void CGhost::reset(const CMap &map) {
    alive_ = true;
    randomTileSet_ = false;
    goingFromDirection_ = NO_DIRECTION;
    CMovingObject::reset(map, homeLocation_);
}

void CGhost::killed(const CMap &map, uint32_t time) {
    location_ = map.getMapCoordinates(homeLocation_);
    timeOfDeath_ = time;
    alive_ = false;
}

bool CGhost::canKill(const CGameInfo &gameInfo) const {
    if (!alive_)
        return false;
    if (gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS)
        return false;

    return true;
}

bool CGhost::canBeKilled(const CGameInfo &gameInfo) const {
    if (!alive_)
        return false;
    if (gameInfo.getGameState() == GAMESTATE_HUNT_ON_GHOSTS)
        return true;

    return false;
}

pair<bool, SMainEntityInfo> CGhost::getMainEntityInfo() const {
    return pair<bool, SMainEntityInfo>(false, {NO_DIRECTION, {0, 0}});
}
