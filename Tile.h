#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Castle.h"

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 450;
const int TILE_SPRITES = 12;

enum {
 TILE_GRASS  ,
 TILE_VINES ,
 TILE_TREE1  ,
 TILE_PONDTOPLEFT ,
 TILE_PONDBOTTOMLEFT  ,
 TILE_STONE1  ,
 TILE_PONDTOPRIGHT  ,
 TILE_PONDBOTTOMRIGHT  ,
 TILE_BUSH1 ,
 TILE_TREE2  ,
 TILE_STONE2 ,
 TILE_BUSH2  ,
};

class Tile
{
private:
    SDL_Rect TBox;
    int TType;
    SDL_Rect Tclips[TOTAL_TILES] ;
    SDL_Rect *Camera;
    SDL_Surface *screen ;
    SDL_Surface *tileSheet ;
    void blitTile( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );


public:
    Tile( int x, int y, int tileType ,SDL_Surface* screen ,SDL_Rect *Camera, SDL_Surface* tileSheet  );
    void showTile();
    int getTileType();
    SDL_Rect* getTileBox();
};

bool touchesObstacle( SDL_Rect box, Tile *tiles[] );
bool touchesVines( SDL_Rect box, Tile *tiles[] );


#endif // TILE_H_INCLUDED
