//
// Created by pavel on 29.04.20.
//

#include "CMovingBonus.h"


bool CMovingBonus::canStepOn(EGameObject &object) {
    if(object == GAMEOBJECT_EMPTY || object == GAMEOBJECT_GATE){
        return true;
    }
    return false;
}

CMovingObject::EDirection CMovingBonus::generalbonusDecision(const CMap &map, const SCoordinates &targetCoords) {
    float minDistance = numeric_limits<float>::max();
    EDirection retDir = NO_DIRECTION;
    //Finding the closest neighbour field to the target
    if(goingFromDirection_ != DIRECTION_RIGHT) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_RIGHT);
        if (canStepOn(inDirection)){
            float  dist = calcDistance(targetCoords, location_.tryMove({1,0}));
            if(dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_RIGHT;
            }
        }
    }

    if(goingFromDirection_ != DIRECTION_DOWN) {
        EGameObject inDirection = getTileInDirection(map, DIRECTION_DOWN);
        if (canStepOn(inDirection)){
            float dist = calcDistance(targetCoords, location_.tryMove({0,1}));
            if(dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_DOWN;
            }
        }
    }
    if(goingFromDirection_ != DIRECTION_LEFT){
        EGameObject inDirection = getTileInDirection(map, DIRECTION_LEFT);
        if (canStepOn(inDirection)){
            float dist = calcDistance(targetCoords, location_.tryMove({-1,0}));
            if(dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_LEFT;
            }
        }
    }
    if(goingFromDirection_ != DIRECTION_UP){
        EGameObject inDirection = getTileInDirection(map, DIRECTION_UP);
        if (canStepOn(inDirection)){
            float dist = calcDistance(targetCoords, location_.tryMove({0,-1}));
            if(dist < minDistance) {
                minDistance = dist;
                retDir = DIRECTION_UP;
            }
        }
    }

    if(retDir == NO_DIRECTION){
        retDir = goingFromDirection_;
    }

    return retDir;
}

SCoordinates CMovingBonus::getTargetCoordinates(const CMap &map, const CGameInfo &gameInfo) {
    if(gameInfo.getTime() > timeOfSettingTarget + 1000 * timeForOneTarget){
        timeOfSettingTarget = gameInfo.getTime();
        randomTile_ = map.getRandomTile();
    }

    return randomTile_;
}

CMovingBonus::CMovingBonus(const CMap &map, const CGameInfo &gameInfo)
:
CMovingObject(map, map.getEmptyTileInMiddle()),
goingFromDirection_(NO_DIRECTION)
{
    timeOfSettingTarget = gameInfo.getTime();
    randomTile_ = map.getRandomTile();
}

SCoordinates CMovingBonus::move(const CMap &map, const CGameInfo &gameInfo) {
    float bonusSpeed = gameInfo.calcMovingBonusSpeed();

    EDirection dir = getOpositeDirectionTo(goingFromDirection_);

    //move while there is a still some distance for moving
    while( !areFloatsEqual(bonusSpeed, 0)){
        if(isOnIntersection()){
            dir = generalbonusDecision(map, getTargetCoordinates(map, gameInfo));
            goingFromDirection_ = getOpositeDirectionTo(dir);
        }

        if(goingFromDirection_ == NO_DIRECTION) {
            return {location_.x(), location_.y()};
        }

        SCoordinates moveVector = getMoveVector(dir, bonusSpeed);
        bonusSpeed = innerGridMove(moveVector);
    }

    return location_.get();
}

SGameObjectInfo CMovingBonus::getObjectInfo() const {
    return {location_.get(), GAMEOBJECT_MOVING_BONUS};
}
