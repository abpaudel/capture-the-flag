#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include "Character.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class GameEngine
{
public:
    GameEngine();
    bool run (void);
    void cleanUp();

private:
    int startTicks;
    void startTimer(void);
    bool playGame();
    bool helpPage();
    bool initSDL();
    SDL_Surface *loadImage( std::string filename );
    bool setTiles( Tile *tiles[] );
    bool loadFiles();
    Tile *tiles[TILE_SPRITES];
    void blitSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
    int getTime(void);
    SDL_Event Event;
    SDL_Rect Camera ;
    SDL_Surface* hero;
    SDL_Surface* screen;
    SDL_Surface* enemy;
    SDL_Surface* tileSheet;
    SDL_Surface* castle;
    SDL_Surface* mainmenu;
    SDL_Surface* winningscreen;
    SDL_Surface* losingscreen;
    SDL_Surface* howtoplay;
    SDL_Surface* timeup;
    SDL_Surface* scroll;
    TTF_Font* Ninja;
    SDL_Surface* score;
    SDL_Surface* timer;

};


#endif // GAMEENGINE_H_INCLUDED
