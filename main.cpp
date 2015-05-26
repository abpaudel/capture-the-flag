#include "gameEngine.h"z

int main ( int argc, char** argv )
{
    GameEngine *Game = new GameEngine;
    Game->run();
    Game->cleanUp( );
    return 0;
}



