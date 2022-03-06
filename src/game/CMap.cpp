//
//
// Created by pavel on 27.04.20.

#include "CMap.h"


void CMap::calcEmptyTileInMiddle()  {
    SCoordinates minEmptyCoords;
    float minDist = numeric_limits<float>::max();
    SCoordinates center = {(float) mapSize_.x_ / 2, (float) mapSize_.y_ / 2};

    // find tile that has smallest distance from the middle
    for(int i = 0; i < mapSize_.y_; ++i){
        for(int j = 0; j < mapSize_.x_; ++j){
            SCoordinates current = {(float) j, (float) i};
            float dist = calcDistance(current, center);
            if(dist < minDist){
                if(mapFields_[i][j].objectType_ == GAMEOBJECT_EMPTY){
                    minEmptyCoords = current;
                    minDist = dist;
                }
            }
        }
    }
    middleEmpty_ = minEmptyCoords;
}

CMap::CMap(const vector<vector<SGameObjectInfo>> &mapFields, const vector<SGameObjectInfo> &bonuses){
    mapFields_= mapFields;
    for(const auto & it: bonuses){
        bonuses_.push_back(it);
        backUpOfBonuses_.push_back(it);
    }

    mapSize_.y_ = mapFields.size();
    mapSize_.x_ = mapFields[0].size();

    calcEmptyTileInMiddle();

    srand (time(nullptr));
}

pair<bool,SGameObjectInfo> CMap::pickBonus(SCoordinates &coordinates) {
    // check if some bonus coordinates aren't the same
    for(auto it = bonuses_.cbegin(); it != bonuses_.end() ;++it) {
        if(areFloatsEqual(it->location_.x_, coordinates.x_) && areFloatsEqual(it->location_.y_, coordinates.y_)){
                SGameObjectInfo tmp = *it;
                bonuses_.erase(it);
                return make_pair(true, tmp);
        }
    }
    return make_pair(false, SGameObjectInfo());
}

void CMap::reset() {
    bonuses_ = backUpOfBonuses_;
}

CMap::CMapCoordinates CMap::getMapCoordinates(const SCoordinates &coordinates) const {
    return CMap::CMapCoordinates(mapSize_, coordinates);
}

void CMap::getStaticBonuses(vector<SGameObjectInfo> &toFill) const {
    for(auto & it : bonuses_){
        toFill.push_back( { it.location_, it.objectType_} );
    }
}

SSize CMap::mapSize() const {
    return mapSize_;
}

EGameObject CMap::getField(const SCoordinates &coordinates) const {
    int x = (int) (coordinates.x_ + 0.002);
    int y = (int) (coordinates.y_ + 0.002);
    if(x >= mapSize_.x_ || y >= mapSize_.y_)
        throw invalid_argument("Map indexes are out of range!");

    return mapFields_[y][x].objectType_;
}

SCoordinates CMap::getRandomTile() const {
    float x = rand() % mapSize_.x_;
    float y = rand() % mapSize_.y_;
    return { x, y};
}

SCoordinates CMap::getEmptyTileInMiddle() const {
    return middleEmpty_;
}
