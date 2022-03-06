//
// Created by pavel on 22.05.20.
//

#include "CMovingObject.h"

float CMovingObject::getSpeedInsideBoundaries(float speed) const {
    if(speed > MAX_MOVING_OBJECT_SPEED){
        return MAX_MOVING_OBJECT_SPEED;
    } else if(speed < MIN_MOVING_OBJECT_SPEED){
        return MIN_MOVING_OBJECT_SPEED;
    }

    return speed;
}

void CMovingObject::reset(const CMap &map, SCoordinates &coordinates) {
    location_ = map.getMapCoordinates(coordinates);
}

float CMovingObject::innerGridMove(const SCoordinates &moveVector) {
    //in which axis will be the move
    if (areFloatsEqual(moveVector.y_, 0)) {
        float moveX = getSpeedInsideBoundaries(moveVector.x_);
        //works for negative and positive numbers

        float oldBase = floor(location_.x());
        float newBase = floor(location_.x() + moveX);
        // check possible cases
        // there is a whole number change in coordinates (example: 3.98 -> 4.02 or 3.00 -> 3.02)
        if(!areFloatsEqual(oldBase, newBase)){
            if(moveX > 0){
                //right
                if(areFloatsEqual(location_.x(), newBase)){
                    // 3.00 -> 3.02
                    location_.moveX(moveX);
                    return 0.0f;
                } else {
                    //3.98 -> 4.02
                    float rest = (location_.x() + moveX) - newBase;
                    location_.moveX(moveX - rest);
                    return rest;
                }
            } else {
                //left
                if(areFloatsEqual(location_.x(), oldBase)){
                    // 3.00 -> 2.98
                    location_.moveX(moveX);
                    return 0.0f;
                } else {
                    // 3.24 -> 3.20
                    float rest = moveX + (location_.x() - oldBase);
                    location_.moveX(moveX - rest);
                    return -rest;
                }
            }
        } else {
            // there is no whole number change in coordinates (example: 3.56 -> 3.60)
            location_.moveX(moveX);
            return 0.0f;
        }


    } else {
        float moveY = getSpeedInsideBoundaries(moveVector.y_);
        //works for negative and positive numbers
        float oldBase = floor(location_.y());
        float newBase = floor(location_.y() + moveY);
        // check possible cases
        // there is a whole number change in coordinates (example: 3.98 -> 4.02 or 3.00 -> 3.02)
        if(!areFloatsEqual(oldBase, newBase)){
            if(moveY > 0){
                //down
                if(areFloatsEqual(location_.y(), newBase)){
                    // 3.00 -> 3.02
                    location_.moveY(moveY);
                    return 0.0f;
                } else {
                    //3.98 -> 4.02
                    float rest = (location_.y() + moveY) - newBase;
                    location_.moveY(moveY - rest);
                    return rest;
                }
            } else {
                //up
                if(areFloatsEqual(location_.y(), oldBase)){
                    // 3.00 -> 2.98
                    location_.moveY(moveY);
                    return 0.0f;
                } else {
                    // 3.24 -> 3.20
                    float rest = moveY + (location_.y() - oldBase);
                    location_.moveY(moveY - rest);
                    return -rest;
                }
            }
        } else {
            // there is no whole number change in coordinates (example: 3.56 -> 3.60)
            location_.moveY(moveY);
            return 0.0f;
        }
    }
}

CMovingObject::EDirection CMovingObject::getOpositeDirectionTo(EDirection directon) {
    switch (directon) {
        case DIRECTION_LEFT:
            return DIRECTION_RIGHT;
        case DIRECTION_UP:
            return DIRECTION_DOWN;
        case DIRECTION_RIGHT:
            return DIRECTION_LEFT;
        case DIRECTION_DOWN:
            return DIRECTION_UP;
        default:
            return NO_DIRECTION;
    }
}

SCoordinates CMovingObject::getMoveVector(CMovingObject::EDirection direction, float speed) {
    switch(direction){
        case DIRECTION_LEFT:
            return {-speed, 0};
        case DIRECTION_UP:
            return {0, -speed};
        case DIRECTION_RIGHT:
            return {speed, 0};
        case DIRECTION_DOWN:
            return {0, speed};
        default: //case NO_DIRECTION:
            return {0,0};
    }
}

EGameObject CMovingObject::getTileInDirection(const CMap &map, CMovingObject::EDirection direction) const {
    switch(direction){
        case DIRECTION_LEFT:
            return map.getField(location_.tryMove({-1,0}));
        case DIRECTION_UP:
            return map.getField(location_.tryMove({0,-1}));
        case DIRECTION_RIGHT:
            return map.getField(location_.tryMove({1,0}));
        case DIRECTION_DOWN:
            return map.getField(location_.tryMove({0,1}));
        default: //case NO_DIRECTION:
            return map.getField({location_.x(), location_.y()});
    }
}

CMovingObject::CMovingObject(const CMap &map, const SCoordinates &location) : location_(
        map.getMapCoordinates(location)) {
}

bool CMovingObject::isOnIntersection() const {
    return areFloatsEqual(location_.x(), round(location_.x())) &&
           areFloatsEqual(location_.y(), round(location_.y()));
}