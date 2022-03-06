//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CMAP_H
#define PA2_2_SEMESTRALKA_CMAP_H

#include <vector>
#include <stdexcept>
#include <list>
#include <memory>
#include <cmath>
#include "../SSize.h"
#include "SGameObjectInfo.h"
#include "../parameters.h"
#include "../functions.h"
#include <ctime>
#include <limits>

using namespace std;

/// A class representing map in a game
class CMap {
    SCoordinates middleEmpty_; ///< empty tile closest to the middle
    SSize mapSize_; ///< size of a map
    vector<vector<SGameObjectInfo>> mapFields_; ///< fields of the map in the matrix
    list<SGameObjectInfo> bonuses_; ///< still not picked bonuses
    list<SGameObjectInfo> backUpOfBonuses_; ///< all bonuses loaded in the beginning

    /// Cal's empty tile closest to the middle
    void calcEmptyTileInMiddle();
public:
    /// Class that represents coordinates in a (CMap) map
    /**
     * Its modulating wrapper around SCoordinates
     * */
    class CMapCoordinates{
        friend class CMap; ///< only CMap can construct CMapCoordinates
        SSize size_; ///< size of the CMap that constructed CMapCoordinates
        SCoordinates coordinates_; ///< coordinates in the map
        /// A constructor construct CMapCoordinates of given arguments
        CMapCoordinates(const SSize &size, const SCoordinates &coordinates): size_(size), coordinates_(coordinates){ runModulo(coordinates_);}
        /// Method that modulates by the map size in special way so the objects in game can move through the borders of the map
        /**
         * @param[in] a number to be modulated
         * @param[in] modulo modulo
         * @return returns modulated float
         * */
        static float modulo( float a, unsigned int modulo){
            if(areFloatsEqual(a, (float) modulo))
                return -0.9f;
            if(areFloatsEqual(a, 0))
                return 0.0f;
            if(a < - 0.9f)
                return fmod((fmod(a, modulo) + modulo), modulo) + 0.9;
            if(!areFloatsEqual( fmod(a, modulo), a)){
                return fmod(a, modulo) - 0.9f;
            } else {
                return fmod(a, modulo);
            }
            //return fmod(a, modulo);
        }
        /// runs modul on the inner coordinates
        /**
         * @param[in,out] coordinates coordinates to be modulated
         * */
        void runModulo(SCoordinates &coordinates) const {
            coordinates.x_ = modulo(coordinates.x_, size_.x_);
            coordinates.y_ = modulo(coordinates.y_, size_.y_);
        }
    public:
        /// Returns coordinates if CMapCoordinates would be moved by moveVector
        /**
         * @param[in] moveVector vector which determines the move
         * @return new possible coordinates are returned
         * */
        SCoordinates tryMove(const SCoordinates &moveVector) const{
            SCoordinates ret;
            ret.x_ = coordinates_.x_ + moveVector.x_;
            ret.y_ = coordinates_.y_ + moveVector.y_;
            runModulo(ret);
            return ret;
        }
        /// move coordinates in X direction
        /**
         * @param howMuch how much will be coordinates moved in x direction
         * */
        void moveX( float howMuch){
            coordinates_.x_ += howMuch;
            runModulo(coordinates_);
        }

        /// move coordinates in Y direction
        /**
         * @param howMuch how much will be coordinates moved in y direction
         * */
        void moveY( float howMuch){
            coordinates_.y_ += howMuch;
            runModulo(coordinates_);
        }
        /// returns x coordinate
        /**
         * @return the x coordinate of the coordinates
         * */
        inline float x() const{
            return coordinates_.x_;
        }
        /// returns y coordinate
        /**
         * @return the y coordinate of the coordinates
         * */
        inline float y() const{
            return coordinates_.y_;
        }
        ///return's coordinates
        /**
         * @return the inner coordinates
         * */
        inline SCoordinates get() const{
            return coordinates_;
        }
    };
    /// A constructor of CMap
    /**
     * @param[in] mapFields fields of the map, that will create the map
     * @param[in] bonuses bonuses on the created map
     * */
    CMap( const vector<vector<SGameObjectInfo>> &mapFields, const vector<SGameObjectInfo> &bonuses);
    /// Check if bonus can be picked
    /**
     * @param[in] coordinates coordinates that will be checked for bonus
     * @return first value determines if some bonus was picked. If was some picked, the information about it will be stored in the second value
     * */
    pair<bool,SGameObjectInfo> pickBonus(SCoordinates &coordinates);
    /// Resets the map (bonuses)
    void reset();
    /// returns map CMapCoordinates set by SCoordinates and CMap
    /**
     * @param[in] coordinates CMapCoordinates will be created with those coordinates
     * @return CMapCoordinates created by coordinates and CMap will be returned
     * */
    CMapCoordinates getMapCoordinates(const SCoordinates & coordinates) const;
    /// Fill all static bonuses that were not picked
    /**
     * @param[out] toFill vector that will be filled with remaining (still not picked) bonuses
     * */
    void getStaticBonuses(vector<SGameObjectInfo> &toFill) const;
    /// get size of map
    /**
     * @return structure representing map size
     * */
    SSize mapSize() const;
    /// returns map field of the map (not bonuses)
    /**
     * @param[in] coordinates Map object on those coordinates will be returned
     * @return object that is on given coordinates
     * */
    EGameObject getField(const SCoordinates &coordinates) const;
    /// returns random tile in the map
    /**
     * @return Method returns some random coordinates in the map
     * */
    SCoordinates getRandomTile() const;
    /// Returns closest tile to the middle that is empty
    /**
     * @return closest tile to the middle that is empty
     * */
    SCoordinates getEmptyTileInMiddle() const;
};

#endif //PA2_2_SEMESTRALKA_CMAP_H