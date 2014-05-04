#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char* args[])
{

    Game *pGame = new Game();
    pGame->run();
    delete pGame;


    return 0;
}
