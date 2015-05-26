#ifndef BLITSURFACES_H_INCLUDED
#define BLITSURFACES_H_INCLUDED




void blitSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}



#endif // BLITSURFACES_H_INCLUDED

