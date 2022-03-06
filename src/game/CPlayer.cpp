//
// Created by pavel on 27.04.20.
//

#include "CPlayer.h"


void CPlayer::updateDirection(const CMap &map) {

    if(nextDirection_ == getOpositeDirectionTo(currentDirection_) && nextDirection_ != NO_DIRECTION){
        currentDirection_ = nextDirection_;
        nextDirection_ = NO_DIRECTION;
        return;
    }

    //its intersection
    if(isOnIntersection()){
        // is next direction set
        if(nextDirection_ != NO_DIRECTION){
            // check if is possible to go in the next direction
            EGameObject tileInDirection = getTileInDirection(map, nextDirection_);
            if(tileInDirection == GAMEOBJECT_EMPTY){
                currentDirection_ = nextDirection_;
                nextDirection_ = NO_DIRECTION;
            }
        }
        //check if its possible to go in current direction, stop if its not possible
        if(currentDirection_ != NO_DIRECTION){
            EGameObject tileInDirection = getTileInDirection(map, currentDirection_);
            if(tileInDirection != GAMEOBJECT_EMPTY){
                currentDirection_ = NO_DIRECTION;
                nextDirection_ = NO_DIRECTION;
            }
        }
    }
}

CPlayer::CPlayer(const CMap &map, const SCoordinates &coordinates)
:
CMovingObject(map, coordinates),
homeCoordinates_(coordinates),
currentDirection_(NO_DIRECTION),
nextDirection_(NO_DIRECTION),
alive_(true)
{
}

void CPlayer::changeDirection(CMovingObject::EDirection direction) {
    nextDirection_ = direction;
}

SCoordinates CPlayer::move(const CMap &map, const CGameInfo &gameInfo, CPickBonusCallable *pickBonusCallable) {
    if(!alive_){
        return location_.get();
    }

    if(currentDirection_ == NO_DIRECTION && nextDirection_ == NO_DIRECTION){
        return location_.get();
    }

    float playerSpeed = gameInfo.calcPlayerSpeed();
    //move while there is a still some distance for moving
    while( !areFloatsEqual(playerSpeed, 0)){
        updateDirection(map);
        if(currentDirection_ == NO_DIRECTION) {
            return {location_.x(), location_.y()};
        }

        SCoordinates moveVector = getMoveVector(currentDirection_, playerSpeed);
        //logMessage("CPlayer coordinates: "s + to_string(moveVector.x_) + ":"s + to_string(moveVector.y_));
        playerSpeed = innerGridMove(moveVector);

        if(isOnIntersection()){
            pickBonusCallable->pickBonus();
        }
    }

    return location_.get();
}

void CPlayer::killed() {
    alive_ = false;
}

void CPlayer::reset(const CMap &map) {
    currentDirection_ = NO_DIRECTION;
    nextDirection_ = NO_DIRECTION;
    alive_ = true;
    CMovingObject::reset(map, homeCoordinates_);
}

SMainEntityInfo CPlayer::getMainEntityInfo() const{
    return {currentDirection_, location_.get()};
}

SGameObjectInfo CPlayer::getObjectInfo() const {
    switch (currentDirection_) {
        case DIRECTION_LEFT:
            return {location_.get(), GAMEOBJECT_PLAYER, EGameObjectDirection::DIRECTION_LEFT};
        case DIRECTION_UP:
            return {location_.get(), GAMEOBJECT_PLAYER, EGameObjectDirection::DIRECTION_UP};
        case DIRECTION_RIGHT:
            return {location_.get(), GAMEOBJECT_PLAYER, EGameObjectDirection::DIRECTION_RIGHT};
        case DIRECTION_DOWN:
            return {location_.get(), GAMEOBJECT_PLAYER, EGameObjectDirection::DIRECTION_DOWN};
        default:
            return {location_.get(), GAMEOBJECT_PLAYER, EGameObjectDirection::NO_DIRECTION};
    }
}

