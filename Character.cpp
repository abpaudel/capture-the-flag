#include "Character.h"

Enemy::Enemy(int posx, int posy,int dir, SDL_Surface* screen , SDL_Rect *Camera , SDL_Surface* enemy ){

    xVel = 5;
    yVel = 0;

    cBox.x = posx;
    cBox.y = posy;

    cBox.w = CHARACTER_WIDTH;
    cBox.h = CHARACTER_HEIGHT;
    frame = 0;
    status = dir;

    this->screen = screen;
    this->Camera = Camera;
    this->enemy = enemy;

    for(int x = 0; x < 4 ; x++){
        for(int y = 0; y < 4; y++){
           eClips[ x ][ y ].x = y * CHARACTER_WIDTH;
           eClips[ x ][ y ].y = x * CHARACTER_HEIGHT;
           eClips[ x ][ y ].w =  CHARACTER_WIDTH;
           eClips[ x ][ y ].h =  CHARACTER_HEIGHT;
        }
    }

    if (dir == 2){
        minX = posx;
        maxX = posx + 208;
    }
    else if (dir == 1){
        maxX = posx;
        minX = posx - 208;
    }
}

void Enemy::move()
{
   if(cBox.x == minX){
    status = CHARACTER_RIGHT;
    xVel = 2;
    cBox.x +=xVel;
   }
   else if(cBox.x == maxX){
    status = CHARACTER_LEFT;
    xVel = -2;
    cBox.x +=xVel;
   }
    else if(cBox.x < maxX && status == CHARACTER_RIGHT){
    cBox.x +=xVel;
   }
   else if(cBox.x > minX && status == CHARACTER_LEFT){
    cBox.x +=xVel;
   }
}

void Enemy::show(){
    if( xVel < 0 ){
        status = CHARACTER_LEFT;
        frame++;
    }
    else if( xVel > 0 ){
        status = CHARACTER_RIGHT;
        frame++;
    }
    else
        frame = 0;

    if( frame >= 4 )
        frame = 0;


    if( checkCollision( cBox , Camera ) == true ){
    if( status == CHARACTER_RIGHT )
        blitCharacter( cBox.x - Camera->x,cBox.y - Camera->y, enemy, screen, &eClips[ CHARACTER_RIGHT ][ frame ] );
    else if( status == CHARACTER_LEFT )
        blitCharacter( cBox.x - Camera->x,cBox.y - Camera->y, enemy, screen, &eClips[ CHARACTER_LEFT ][ frame ] );

    }
}


SDL_Rect* Enemy::getBox(){
    return &cBox;
}

Hero::Hero(SDL_Surface *screen, SDL_Rect *Camera , SDL_Surface *hero, Enemy **enm , Tile **tiles, Castle *flag){

    xVel = 0;
    yVel = 0;

    cBox.x = 80;
    cBox.y = 120;
    xMove = 80;
    yMove = 120;

    lives = 3;
    win = false;

    cBox.w = CHARACTER_WIDTH;
    cBox.h = CHARACTER_HEIGHT;
    frame = 0;
    status = CHARACTER_RIGHT;
    this->screen = screen;
    this->hero = hero;
    this->Camera = Camera;

    this->enm = enm;
    this->tiles = tiles;
    this->flag = flag;

    for ( int i=0; i<SDLK_LAST; ++i ) {
        this->keys[ i ] = 0 ;
      }
    for(int x = 0; x < 4 ; x++){
        for(int y = 0; y < 4; y++){
           Hclip[ x ][ y ].x = y * CHARACTER_WIDTH;
           Hclip[ x ][ y ].y = x * CHARACTER_HEIGHT;
           Hclip[ x ][ y ].w =  CHARACTER_WIDTH;
           Hclip[ x ][ y ].h =  CHARACTER_HEIGHT;
        }
    }
}

void Hero::onKeyDown( SDL_Event* Event ) {
    keys[ Event->key.keysym.sym ] = 1 ;
    switch( Event->key.keysym.sym ){
        case SDLK_UP: yVel -= CHARACTER_HEIGHT / 12; break;
        case SDLK_DOWN: yVel += CHARACTER_HEIGHT / 12; break;
        case SDLK_LEFT: xVel -= CHARACTER_WIDTH / 8; break;
        case SDLK_RIGHT: xVel += CHARACTER_WIDTH / 8; break;
    }
}

void Hero::onKeyUp( SDL_Event* Event ) {
    keys[ Event->key.keysym.sym ] = 0 ;
    switch( Event->key.keysym.sym ){
        case SDLK_UP: yVel += CHARACTER_HEIGHT / 12; break;
        case SDLK_DOWN: yVel -= CHARACTER_HEIGHT / 12; break;
        case SDLK_LEFT: xVel += CHARACTER_WIDTH / 8; break;
        case SDLK_RIGHT: xVel -= CHARACTER_WIDTH / 8; break;
    }
}

void Hero::move()
{
    if ( keys[SDLK_LEFT] ) {
        cBox.x += xVel ;
        xMove += xVel;
    }
    else if ( keys[SDLK_RIGHT] ) {
        cBox.x += xVel ;
        xMove += xVel;
    }
    else if ( keys[SDLK_UP] ) {
        cBox.y += yVel;
        yMove += yVel;
    }
    else if ( keys[SDLK_DOWN] ) {
        cBox.y += yVel;
        yMove += yVel;
      }



   if( ( xMove < 0 ) || ( xMove + CHARACTER_WIDTH > SCREEN_WIDTH )|| touchesObstacle( cBox, tiles )){
        xMove -= xVel;
        cBox.x -= xVel;
    }


    if( ( yMove < 0 ) || ( yMove + CHARACTER_HEIGHT > SCREEN_HEIGHT ) || touchesObstacle( cBox, tiles )){
        yMove -= yVel;
        cBox.y -= yVel;
    }
    for(int i = 0 ; i < TOTAL_ENEMY ; i++ ){
        if (checkCollision(cBox, enm[i]->getBox()) ){
            cBox.x -= xVel;
            cBox.y -= yVel;
            xMove -= xVel;
            yMove -= yVel;
            lives -= 1;
            cBox.x = 80;
            cBox.y = 120;
            xMove = 80;
            yMove = 120;
            Camera->x = 0;
            Camera->y = 0;
            status =CHARACTER_RIGHT;
            frame = 0;

        }
    }
     if ( touchesVines(cBox , tiles)){
            cBox.x -= xVel;
            cBox.y -= yVel;
            xMove -= xVel;
            yMove -= yVel;
            lives -= 1;
            cBox.x = 80;
            cBox.y = 120;
            xMove = 80;
            yMove = 120;
            Camera->x = 0;
            Camera->y = 0;
            status =CHARACTER_RIGHT;
            frame = 0;
    }
    if (checkCollision(cBox, flag->getCasBox())){
            win = true;
    }

}

void Hero::show()
{
    if( xVel < 0 ){
        status = CHARACTER_LEFT;
        frame++;
    }
    else if( xVel > 0 ){
        status = CHARACTER_RIGHT;
        frame++;
    }
    else if( yVel < 0 ){
        status = CHARACTER_UP;
        frame++;
    }
    else if( yVel > 0 ){
        status = CHARACTER_DOWN;
        frame++;
    }
    else
        frame = 0;

    if( frame >= 4 )
        frame = 0;

    if( status == CHARACTER_RIGHT )
        blitCharacter( xMove,yMove, hero, screen, &Hclip[ CHARACTER_RIGHT ][ frame ] );
    else if( status == CHARACTER_LEFT )
        blitCharacter( xMove,yMove, hero, screen, &Hclip[ CHARACTER_LEFT ][ frame ] );
    else if( status == CHARACTER_UP )
        blitCharacter( xMove, yMove, hero, screen, &Hclip[ CHARACTER_UP ][ frame ] );
    else if( status == CHARACTER_DOWN )
        blitCharacter( xMove, yMove, hero, screen, &Hclip[ CHARACTER_DOWN ][ frame ] );

}
int Hero::getLives(){
    return this->lives;
}

void Hero::setCamera()
{
   if (status == CHARACTER_RIGHT && (cBox.x-Camera->x) >= SCREEN_WIDTH/2){

        Camera->x += xVel;
        if (Camera->x <= LEVEL_WIDTH - SCREEN_WIDTH ) xMove -= xVel;

    }

    else if(status == CHARACTER_LEFT && (cBox.x-Camera->x) <= SCREEN_WIDTH/2){
        Camera->x += xVel;
        if (Camera->x >= 0) xMove -= xVel;
    }

    else if (status == CHARACTER_DOWN && (cBox.y-Camera->y) >= SCREEN_HEIGHT/2){
        Camera->y += yVel;
        if (Camera->y <= LEVEL_HEIGHT - SCREEN_HEIGHT ) yMove -= yVel;
    }

    else if(status == CHARACTER_UP && (cBox.y-Camera->y) <= SCREEN_HEIGHT/2){
        Camera->y += yVel;
        if (Camera->y >= 0) yMove -= yVel;
    }



    if( Camera->x < 0 )
        Camera->x = 0;
    if( Camera->y < 0 )
        Camera->y = 0;
    if( Camera->x > LEVEL_WIDTH - Camera->w )
        Camera->x = LEVEL_WIDTH - Camera->w;
    if( Camera->y > LEVEL_HEIGHT - Camera->h )
        Camera->y = LEVEL_HEIGHT - Camera->h;
}

bool Hero::flagCaptured(){
    return win;
}

void Character::blitCharacter( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}
