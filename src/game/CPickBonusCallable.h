//
// Created by pavel on 24.05.20.
//

#ifndef PA2_2_SEMESTRALKA_PICKBONUSCALLABLE_H
#define PA2_2_SEMESTRALKA_PICKBONUSCALLABLE_H

/// Class that is interface for Player to call some object that handles if some bonus was picked
class CPickBonusCallable{
public:
    /// method for calling check of picking bonus
    virtual void pickBonus() = 0;
};

#endif //PA2_2_SEMESTRALKA_PICKBONUSCALLABLE_H