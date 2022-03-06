#include <iostream>
#include <SDL2/SDL.h>
#include "view/CView.h"
#include "game/SGameObjectInfo.h"
#include "CController.h"

using namespace std;

int main(int argc, char **argv) {
    // correct use of calling the controller and playing the game
    CController controler;
    if (!controler.loadGame(argc, argv)) {
        return 1;
    }
    controler.startGame();
    controler.playGame();
}