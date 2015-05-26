#ifndef CASTLE_H_INCLUDED
#define CASTLE_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

bool checkCollision( SDL_Rect R1, SDL_Rect *R2 );

class Castle{
private:
    SDL_Rect CastleBox ;
    SDL_Rect *Camera;
    SDL_Surface *screen ;
    SDL_Surface *castle ;
    SDL_Rect CastleClip;
    void blitCastleSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );

public:
    Castle(int posx, int posy , SDL_Surface* screen , SDL_Rect *Camera , SDL_Surface* castle);
    void showCastle();
    SDL_Rect* getCasBox();

};




#endif // CASTLE_H_INCLUDED
