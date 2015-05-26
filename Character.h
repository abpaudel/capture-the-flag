#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "Tile.h"

const int SCREEN_WIDTH = 900 ;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32 ;


const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1240;

const int CHARACTER_WIDTH = 32;
const int CHARACTER_HEIGHT = 48;

const int CHARACTER_DOWN = 0;
const int CHARACTER_LEFT = 1;
const int CHARACTER_RIGHT = 2;
const int CHARACTER_UP = 3;

const int TOTAL_ENEMY = 11;



class Character
{
protected:

    SDL_Rect cBox;
    int xVel , yVel;
    int xMove , yMove;
    int frame;
    int status;
    void blitCharacter( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );

public:
    void virtual move() = 0;
    void virtual show() = 0;


};

class Enemy: public Character
{
private:
    SDL_Surface *screen;
    SDL_Rect *Camera;
    SDL_Surface *enemy ;
    SDL_Rect eClips[ 4 ][ 4 ];
    int maxX , minX;

public:
    Enemy(int posx, int posy,int dir, SDL_Surface* screen , SDL_Rect *Camera , SDL_Surface* enemy );
    void move();
    void show();
    SDL_Rect* getBox();

};

class Hero : public Character
{
private:
    int keys[ SDLK_LAST ] ;
    int lives;
    bool win;
    Enemy **enm;
    Tile **tiles;
    Castle *flag;
    SDL_Surface *screen;
    SDL_Rect *Camera;
    SDL_Surface *hero ;
    SDL_Rect Hclip[ 4 ][ 4 ];



public:
    Hero(SDL_Surface* screen, SDL_Rect *Camera , SDL_Surface* hero, Enemy **enm , Tile **tiles, Castle *flag);
    void onKeyDown( SDL_Event* Event );
    void onKeyUp( SDL_Event* Event );
    void move();
    void show();
    int getLives();
    void setCamera();
    bool flagCaptured();

  };

#endif // CHARACTER_H_INCLUDED
