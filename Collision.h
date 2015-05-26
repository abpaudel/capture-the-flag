#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


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


bool touchesObstacle( SDL_Rect box, Tile *tiles[] )
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( ( tiles[ t ]->getTileType() >= TILE_VINES ) && ( tiles[ t ]->getTileType() <= TILE_BUSH2 ) )
        {
            if( checkCollision( box, &tiles[ t ]->getTileBox() ) == true )
            {
                return true;
         }
        }
    }

    return false;
}

#endif // COLLISION_H_INCLUDED
