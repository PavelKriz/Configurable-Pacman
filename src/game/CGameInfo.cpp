//
// Created by pavel on 27.04.20.
//

#include "CGameInfo.h"

void CGameInfo::checkIfPlayerWon() {
    float ratio = (float) numberOfPickedBonuses_ / numberOfBonuses_;
    if(areFloatsEqual(ratio, 1.0f)){
        timeOfLastChange_ = time_;
        numberOfPickedBonuses_ = 0;
        score_ += LEVEL_DONE_VALUE;
        ++level_;
        currentState_ = GAMESTATE_VICTORY;
    }
}

void CGameInfo::calcTimeToMovingBonus() {
    if(gameParameters_.probabilityOfMovingBonus_ == 100){
        movingBonusesCanBeGenerated_ = false;
    } else {
        nextMovingBonusIn_ = rand() % (gameParameters_.probabilityOfMovingBonus_ + 1);
        lastTimeMovingBonusExisted_ = time_;
    }
}

unsigned int CGameInfo::calcNeutralTimeLength() const{
    float coef = (-1.0f / 10.0f) * level_ + 1.0f;
    if(coef < 0.1f){
        coef = 0.1f;
    }
    int time = 1000.0f * gameParameters_.neutralTimeLength_ * coef;
    if(time < 1000){
        time = 1000;
    }

    return time;
}

CGameInfo::CGameInfo(uint32_t time, SGameParameters gameParameters, unsigned int numberOfBonuses)
:
currentState_(GAMESTATE_HUNT_ON_PLAYER),
timeOfLastChange_(time),
gameParameters_(gameParameters),
numberOfBonuses_(numberOfBonuses),
level_(1),
time_(time)
{
    srand (time);
    calcTimeToMovingBonus();
}

void CGameInfo::bonusWasPicked(const SGameObjectInfo &objectInfo) {
    if(objectInfo.objectType_ == GAMEOBJECT_BASIC_BONUS){
        ++numberOfPickedBonuses_;
        score_ += BASIC_BONUS_VALUE;
    } else if (objectInfo.objectType_ == GAMEOBJECT_KILLER_BONUS){
        ++numberOfPickedBonuses_;
        currentState_ = GAMESTATE_HUNT_ON_GHOSTS;
        timeOfLastChange_ = time_;
    } else if (objectInfo.objectType_ == GAMEOBJECT_MOVING_BONUS){
        movingBonusGenerated_ = false;
        lastTimeMovingBonusExisted_ = time_;
        calcTimeToMovingBonus();
        score_ += MOVING_BONUS_VALUE;
    }
    checkIfPlayerWon();
}

void CGameInfo::updateTime(uint32_t time) {
    time_ = time;
    unsigned int timeFromLastChange = time_ - timeOfLastChange_;
    switch (currentState_) {
        case GAMESTATE_HUNT_ON_PLAYER:
            if(timeFromLastChange > 1000 * gameParameters_.huntOnPlayerTimeLength_){
                timeOfLastChange_ = time_;
                currentState_ = GAMESTATE_NEUTRAL;
            }
            break;
        case GAMESTATE_NEUTRAL:
            if(timeFromLastChange > calcNeutralTimeLength()){
                timeOfLastChange_ = time_;
                currentState_ = GAMESTATE_HUNT_ON_PLAYER;
            }
            break;
        case GAMESTATE_HUNT_ON_GHOSTS:
            if(timeFromLastChange > 1000 * gameParameters_.huntOnGhostsTimeLength_){
                ghostsKilledInRow_ = 0;
                timeOfLastChange_ = time_;
                currentState_ = GAMESTATE_HUNT_ON_PLAYER;
            }
            break;
        case GAMESTATE_LOST_LIFE:
            if(timeFromLastChange > 1000 * LOST_LIFE_DURATION){
                timeOfLastChange_ = time_;
                currentState_ = GAMESTATE_HUNT_ON_PLAYER;
            }
            break;
        case GAMESTATE_VICTORY:
            if(timeFromLastChange > 1000 * WIN_DURATION){
                timeOfLastChange_ = time_;
                currentState_ = GAMESTATE_HUNT_ON_PLAYER;
            }
            break;
        case GAMESTATE_LOST:
            break;
    }
}

bool CGameInfo::generateMovingBonus() {
    if(!movingBonusGenerated_ && movingBonusesCanBeGenerated_){
        if(time_ > lastTimeMovingBonusExisted_ + 1000 * nextMovingBonusIn_){
            movingBonusGenerated_ = true;
            return true;
        }
    }
    return false;
}

void CGameInfo::ghostWasKilled() {
    ++ghostsKilledInRow_;
    score_ += KILLER_BONUS_VALUE * pow(2, ghostsKilledInRow_);
}

void CGameInfo::playerWasKilled() {
    timeOfLastChange_ = time_;
    --lives_;
    if(lives_ == 0){
        currentState_ = GAMESTATE_LOST;
    } else {
        currentState_ = GAMESTATE_LOST_LIFE;
    }
}

void CGameInfo::reset() {
    currentState_ = GAMESTATE_HUNT_ON_PLAYER;
    numberOfPickedBonuses_ = 0;
    ghostsKilledInRow_ = 0;
    score_ = 0;
    lives_ = NUMBER_OF_LIVES;
    level_ = 1;
    timeOfLastChange_ = time_;
    movingBonusGenerated_ = false;
    lastTimeMovingBonusExisted_ = time_;
}

void CGameInfo::movingBonusWasPicked() {
    lastTimeMovingBonusExisted_ = time_;
    movingBonusGenerated_ = false;
}

float CGameInfo::calcGhostSpeed() const {
    if(currentState_ == GAMESTATE_HUNT_ON_GHOSTS){
        return baseSpeed_ * gameParameters_.ghostSpeedCoeficient_ * SCARED_GHOST_SPEED_COEFICIENT;
    } else {
        return baseSpeed_ * gameParameters_.ghostSpeedCoeficient_;
    }
}

float CGameInfo::calcPlayerSpeed() const {
    return baseSpeed_;
}

float CGameInfo::calcMovingBonusSpeed() const {
    return baseSpeed_ * 0.5f;
}

void CGameInfo::getDisplayInfo(SDisplayInfo &toFill) const {
    toFill = {level_, lives_, currentState_, gameParameters_.gameMode_, score_, numberOfPickedBonuses_, numberOfBonuses_};
}

float CGameInfo::getPickedBonusesRatio() const {
    return (float) numberOfPickedBonuses_ / numberOfBonuses_;
}

EGameState CGameInfo::getGameState() const {
    return currentState_;
}

uint32_t CGameInfo::getTime() const{
    return time_;
}


