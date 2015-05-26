#include "Tile.h"

Tile::Tile( int x, int y, int tileType ,SDL_Surface* screen ,SDL_Rect *Camera, SDL_Surface* tileSheet ){
    TBox.x = x;
    TBox.y = y;

    TBox.w = TILE_WIDTH;
    TBox.h = TILE_HEIGHT;

    TType = tileType;
    this->screen = screen;
    this->Camera = Camera;
    this->tileSheet = tileSheet;

    int TileType = 0;
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 3; y++){
           Tclips[ TileType ].x = x * TILE_WIDTH;
           Tclips[ TileType ].y = y * TILE_HEIGHT;
           Tclips[ TileType ].w =  TILE_WIDTH;
           Tclips[ TileType ].h =  TILE_HEIGHT;
           TileType ++;

        }
    }
}

void Tile::showTile(){
    if( checkCollision( TBox ,  Camera ) == true )
        blitTile( TBox.x - Camera->x, TBox.y - Camera->y, tileSheet, screen, &Tclips[ TType ] );
}

int Tile::getTileType(){
    return TType;
}

SDL_Rect* Tile::getTileBox(){
    return &TBox;
}


bool touchesObstacle( SDL_Rect box, Tile *tiles[] )
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( ( tiles[ t ]->getTileType() >= TILE_TREE1 ) && ( tiles[ t ]->getTileType() <= TILE_BUSH2 ) )
        {
            if( checkCollision( box, tiles[ t ]->getTileBox() ) == true )
            {
                return true;
         }
        }
    }
    return false;
}

bool touchesVines( SDL_Rect box, Tile *tiles[] )
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( ( tiles[ t ]->getTileType() == TILE_VINES ) )
        {
            if( checkCollision( box, tiles[ t ]->getTileBox() ) == true )
            {
                return true;
         }
        }
    }

    return false;
}
void Tile::blitTile( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}
