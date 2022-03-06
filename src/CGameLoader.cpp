//
// Created by pavel on 27.04.20.
//

#include "CGameLoader.h"

void CGameLoader::skipRestofLine(ifstream &toBeSkipped) {
    while (toBeSkipped.good()) {
        if (toBeSkipped.get() == '\n')
            break;
    }
}

unsigned int CGameLoader::getMapRowLength(ifstream &toMeasure) {
    unsigned int counter = 0;
    while (toMeasure.good()) {
        if (toMeasure.peek() != '-')
            break;
        else{
            toMeasure.get();
        }
        ++counter;
    }
    if(!toMeasure.good()){
        throw invalid_argument("Invalid map file. ");
    }
    return counter;
}

bool CGameLoader::skipBetweenRowsAndIsEndOfMap(ifstream &toBeSkipped) {
    while (toBeSkipped.good()) {
        char c = toBeSkipped.get();
        if (c == '|')
            return false;
        else if (c == '-')
            return true;
    }
    throw invalid_argument("Invalid map file. The bottom border wasnt found!");
}


void CGameLoader::loadMapRow(SLoadedGame &toLoad, ifstream &mapIfs, int lineIndex, int innerRowLength) {
    toLoad.mapFields_.push_back(vector<SGameObjectInfo>());
    //load elements in a row
    for (int i = 0; i < innerRowLength; ++i) {
        char c = mapIfs.get();
        if (!mapIfs.good())
            throw invalid_argument(
                    "Invalid map file. Error was found on line( index withnout borders): "s + to_string(lineIndex));
        //decide what case it is and save it to correct places
        switch (c) {
            case 'P':
                if (playerWasLoaded)
                    throw invalid_argument("In game can be only one pacman( player)!");
                playerWasLoaded = true;
                toLoad.player_ = {{(float) i, (float) lineIndex}, GAMEOBJECT_PLAYER};
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_EMPTY});
                break;
            case 'X':
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_GATE});
                break;
            case '#':
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_WALL});
                break;
            case ' ':
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_EMPTY});
                break;
            case 'G':
                ghostWasLoaded = true;
                toLoad.ghosts_.push_back({{(float) i, (float) lineIndex}, GAMEOBJECT_RED_GHOST});
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_EMPTY});
                break;
            case '.':
                basicBonusWasLoaded = true;
                toLoad.bonuses_.push_back({{(float) i, (float) lineIndex}, GAMEOBJECT_BASIC_BONUS});
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_EMPTY});
                break;
            case '@':
                toLoad.bonuses_.push_back({{(float) i, (float) lineIndex}, GAMEOBJECT_KILLER_BONUS});
                toLoad.mapFields_[lineIndex].push_back( {{(float) i, (float) lineIndex}, GAMEOBJECT_EMPTY});
                break;
            default:
                // its not a valid symbol
                throw invalid_argument("Invalid symbol in map. That symbol is: "s + c);
        }

    }
}

void CGameLoader::loadConfig(SLoadedGame &toLoad, ifstream &configIfs) {
    //game mode loading
    int gameMode;
    configIfs >> gameMode;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing gameMode.");
    if(gameMode == GAMEMODE_NORMAL_INDEX){
        toLoad.gameParameters_.gameMode_ = EGameMode::GAMEMODE_NORMAL;
    } else if(gameMode == GAMEMODE_HARD_INDEX){
        toLoad.gameParameters_.gameMode_ = EGameMode::GAMEMODE_HARD;
    } else if(gameMode == GAMEMODE_RANDOM_INDEX){
        toLoad.gameParameters_.gameMode_ = EGameMode::GAMEMODE_RANDOM;
    } else {
        throw invalid_argument("Invalid value for game mode!");
    }

    skipRestofLine(configIfs);
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! File isnt complete.");

    // ghost speed percenatge loading
    int ghostsSpeedPercentage;
    configIfs >> ghostsSpeedPercentage;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing ghost speed.");
    if (ghostsSpeedPercentage < 50 || ghostsSpeedPercentage > 200)
        throw invalid_argument("Invalid value for ghost speed!");
    toLoad.gameParameters_.ghostSpeedCoeficient_ = (float) ghostsSpeedPercentage / 100;

    skipRestofLine(configIfs);
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! File isnt complete.");

    // neutral time length loading
    configIfs >> toLoad.gameParameters_.neutralTimeLength_;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing neutral game time length.");
    if (toLoad.gameParameters_.neutralTimeLength_ < 1 || toLoad.gameParameters_.neutralTimeLength_ > 60)
        throw invalid_argument("Invalid value for neutral game time length!");

    skipRestofLine(configIfs);
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! File isnt complete.");

    // hunt on ghosts time length loading
    configIfs >> toLoad.gameParameters_.huntOnGhostsTimeLength_;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing hunt on ghosts time length.");
    if (toLoad.gameParameters_.huntOnGhostsTimeLength_ < 1 || toLoad.gameParameters_.huntOnGhostsTimeLength_ > 60)
        throw invalid_argument("Invalid value for hunt on ghosts time length!");

    skipRestofLine(configIfs);
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! File isnt complete.");

    // hunt on player time length loading
    configIfs >> toLoad.gameParameters_.huntOnPlayerTimeLength_;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing hunt on player time length.");
    if (toLoad.gameParameters_.huntOnPlayerTimeLength_ < 1 || toLoad.gameParameters_.huntOnPlayerTimeLength_ > 60)
        throw invalid_argument("Invalid value for hunt on player time length!");

    skipRestofLine(configIfs);
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! File isnt complete.");

    // loading probability of the moving bonus
    configIfs >> toLoad.gameParameters_.probabilityOfMovingBonus_;
    if (!configIfs.good())
        throw invalid_argument("Invalid config file! Missing probability of moving bonuses.");
    if (toLoad.gameParameters_.probabilityOfMovingBonus_ < 0 || toLoad.gameParameters_.probabilityOfMovingBonus_ > 100)
        throw invalid_argument("Invalid value for probability of moving bonuses!");

}

void CGameLoader::loadMap(SLoadedGame &toLoad, ifstream &mapIfs) {
    // Top of the map border
    unsigned int rowLength = getMapRowLength(mapIfs);
    // skiping
    int innerRowLength = rowLength - 2;
    if (!mapIfs.good())
        throw invalid_argument("Invalid map file.");
    else if (innerRowLength < (int) MIN_SIZE_)
        throw invalid_argument("Map row length is too small.");
    else if (rowLength > 100)
        throw invalid_argument("Map row length is too big.");

    bool end ;

    // Map and left and right borders
    unsigned int lineCounter = 0;
    while (true) {
        end = skipBetweenRowsAndIsEndOfMap(mapIfs);
        if (end)
            break;
        loadMapRow(toLoad, mapIfs, lineCounter, innerRowLength);
        if (mapIfs.get() != '|') {
            throw invalid_argument("Invalid map file. Missing | at the end of map row.");
        }
        if (!mapIfs.good()) {
            throw invalid_argument("Invalid map file.");
        }
        ++lineCounter;
    }

    //check other necessary things
    if (lineCounter < MIN_SIZE_)
        throw invalid_argument("Invalid map file. Number of rows must be at least 6.");

    if (!playerWasLoaded)
        throw invalid_argument("Invalid map file. Map have to contain pacman( player)");

    if (!basicBonusWasLoaded)
        throw invalid_argument("Invalid map file. Map have to contain at least one bonus!");

    if (!ghostWasLoaded)
        throw invalid_argument("Invalid map file. Map have to contain at least one ghost!");

    //bottom border
    int checkRowLength = getMapRowLength(mapIfs);
    if (checkRowLength != (int) rowLength - 1) {
        throw invalid_argument("Invalid map file. Invalid bottom border line.");
    }
}

bool CGameLoader::loadGame(SLoadedGame &toLoad, int argc, char **argv) {
    try {
        // check if the arguments are correct
        if (argc != 3) {
            throw invalid_argument("Wrong arguments! Usage is \"pacman [path to config file] [path to map file]\"");
        }

        // try to open config and map file
        string configFileName(argv[1]);
        string mapFileName(argv[2]);

        ifstream configIfs(configFileName, std::ifstream::in);
        ifstream mapIfs(mapFileName, ifstream::in);
        if (!configIfs.good()) {
            throw invalid_argument("Config file wasnt loaded. Not loaded files path is: " + configFileName +
                                   "\n Usage is \"pacman [path to config file] [path to map file]\"");
        }
        if (!mapIfs.good()) {
            throw invalid_argument("Map file wasnt loaded. Not loaded files path is: " + mapFileName +
                                   "\n Usage is \"pacman [path to config file] [path to map file]\"");
        }

        //try to load map and config file
        loadConfig(toLoad, configIfs);
        loadMap(toLoad, mapIfs);
    } catch (invalid_argument & exception){
        cout << "Program failed." << endl;
        cout << exception.what() << endl;
        return false;
    }
    return true;
}