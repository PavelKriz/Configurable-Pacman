//
// Created by pavel on 27.04.20.
//

#ifndef PA2_2_SEMESTRALKA_CGAMELOADER_H
#define PA2_2_SEMESTRALKA_CGAMELOADER_H

#include "SLoadedGame.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

/// A class that do the game loading from the file
class CGameLoader {
    bool playerWasLoaded = false; ///< if the player was loaded from the map file
    bool basicBonusWasLoaded = false; ///< if at least one basic bonus was loaded from the map file
    bool ghostWasLoaded = false; ///< if at least one ghost was loaded from map file

    static const unsigned int MIN_SIZE_ = 3; ///< minimal size of the map

    /// skips rest of the line, used in loading of the config file
    /**
     * @param[in,out] toBeSkipped file stream in which will be skipped the rest of the line
     * */
    void skipRestofLine(ifstream &toBeSkipped);
    /// returns the map row length, used in the map file loading
    /**
     * @param[in,out] toMeasure file stream in which will be the map row size measured
     * @return outer width of the map row (with the borders)
     * */
    unsigned int getMapRowLength(ifstream &toMeasure);
    /// skips other spaces between rows
    /**
     * @param[in,out] toBeSkipped file stream in which will be skipped the rest between map rows
     * */
    bool skipBetweenRowsAndIsEndOfMap(ifstream &toBeSkipped);
    /// loads map row
    /**
     * @param[in] toLoad structure where the data are saved from files
     * @param[in,out] mapIfs input file stream from which the map is read
     * @param[in] lineIndex index of the loading line/row
     * @param[in] innerRowLength width of the row without the map borders
     * */
    void loadMapRow(SLoadedGame &toLoad, ifstream &mapIfs, int lineIndex, int innerRowLength);
    /// loads config file
    /**
     * @param[in] toLoad structure where the data are saved from files
     * @param[in,out] configIfs input file stream from which the configuration is read
     * */
    void loadConfig(SLoadedGame &toLoad, ifstream &configIfs);
    /// loads map file
    /**
     * @param[in] toLoad structure where the data are saved from files
     * @param[in,out] configIfs input file stream from which the map is read
     * */
    void loadMap(SLoadedGame &toLoad, ifstream &mapIfs);

public:
    /// loads the game and fills the loaded game
    /**
     * @param[in] toLoad structure where the data are saved from files
     * @param[in] argc number of arguments used when the game was called from terminal
     * @param[in] argv c strings with the arguments used when the game was called from terminal
     * */
    bool loadGame(SLoadedGame &toLoad, int argc, char **argv);
};

#endif //PA2_2_SEMESTRALKA_CGAMELOADER_H