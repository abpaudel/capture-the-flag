#include "Castle.h"


Castle::Castle(int posx, int posy , SDL_Surface* screen , SDL_Rect *Camera , SDL_Surface* castle){

    CastleBox.x = posx;
    CastleBox.y = posy;
    CastleBox.w = 160;
    CastleBox.h = 160;

    this->screen = screen;
    this->Camera = Camera;
    this->castle = castle;

    CastleClip.x = 0;
    CastleClip.y = 0;
    CastleClip.w = 160;
    CastleClip.h = 160;
}

SDL_Rect* Castle::getCasBox(){
    return &CastleBox;
}

void Castle::showCastle(){
    if(checkCollision(CastleBox, Camera))
        blitCastleSurface(CastleBox.x - Camera->x, CastleBox.y-Camera->y, castle, screen , &CastleClip);


}
void Castle::blitCastleSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}


bool checkCollision( SDL_Rect R1, SDL_Rect *R2 )
{
    int leftR1, leftR2;
    int rightR1, rightR2;
    int topR1, topR2;
    int bottomR1, bottomR2;

    leftR1 = R1.x;
    rightR1 = R1.x + R1.w;
    topR1 = R1.y;
    bottomR1 = R1.y + R1.h;

    leftR2 = R2->x;
    rightR2 = R2->x + R2->w;
    topR2 = R2->y;
    bottomR2 = R2->y + R2->h;

    if( bottomR1 <= topR2 )
        return false;

    if( topR1 >= bottomR2 )
        return false;

    if( rightR1 <= leftR2 )
        return false;

    if( leftR1 >= rightR2 )
        return false;

    return true;
}
