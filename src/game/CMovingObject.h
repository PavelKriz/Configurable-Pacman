//
// Created by pavel on 22.05.20.
//

#ifndef PA2_2_SEMESTRALKA_CMOVINGOBJECT_H
#define PA2_2_SEMESTRALKA_CMOVINGOBJECT_H


#include "CMap.h"
#include "../SCoordinates.h"

using namespace std;

/// A class that is ancestor of all moving objects in a game
class CMovingObject {
public:
    /// Enum of all directions that can moving object go in
    enum EDirection {
        DIRECTION_LEFT, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, NO_DIRECTION
    };
private:
    const float MAX_MOVING_OBJECT_SPEED = 0.45f; ///< max speed of moving object
    const float MIN_MOVING_OBJECT_SPEED = -0.45f; ///< min speed of moving object

    /// Method that check if speed is in valid range, if not then the speed is cut
    /**
     * @param[in] speed to be get into boundaries
     * @return speed that is already in the boundaries
     * */
    float getSpeedInsideBoundaries(float speed) const;
protected:
    CMap::CMapCoordinates location_; ///< location of the moving object
    /// Method resets the moving object to initial state
    /**
     * @param[in] map map where the moving object is
     * @param[in] coordinates new location after the rest
     * */
    void reset(const CMap &map, SCoordinates &coordinates);
    /// Method that do the move in the space
    /**
     * @param[in] moveVector vector that will move the object (x or y must be 0 in the vector)
     * @return how much distance still wasnt used
     * */
    float innerGridMove(const SCoordinates & moveVector);
    /// Method returns opposite direction to given direction
    /**
     * @param[in] directon input direction
     * @return opposite direction to the input direction
     * */
    static EDirection getOpositeDirectionTo(EDirection directon);
    /// Method returns move vector constructed from given arguments
    /**
     * @param[in] direction direction in which the move vector will be constructed
     * @param[in] speed determines how big will be the move vector
     * @return the move vector is returned in form of coordinates ( vector goes from zero origin to these coordinates)
     * */
    static SCoordinates getMoveVector(EDirection direction, float speed);
    /// Method returns neighbour tile from map in given direction
    /**
     * @param[in] map map where the moving object is
     * @param[in] direction determines in which direction the tile will be
     * @return the neighbour tile in the given direction
     * */
    EGameObject getTileInDirection(const CMap &map, EDirection direction) const;
public:
    /// A constructor of the moving object
    /**
     * @param[in] map map where the moving object is
     * @param[in] location the location where the moving object will be after creation
     * */
    CMovingObject(const CMap & map, const SCoordinates &location);
    /// checks whether is object on intersection
    /**
     * @return true if is on intersection (coordinates with whole numbers, for example {32.0, 25.0})
     * */
    bool isOnIntersection() const;
};


#endif //PA2_2_SEMESTRALKA_CMOVINGOBJECT_H
