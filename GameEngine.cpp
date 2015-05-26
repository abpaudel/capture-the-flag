#include "gameEngine.h"

const int FRAMES_PER_SECOND =  13;

GameEngine::GameEngine( ){
    screen = NULL;
    startTicks = 0;
    Camera.x = 0;
    Camera.y = 0;
    Camera.w = SCREEN_WIDTH;
    Camera.h = SCREEN_HEIGHT;
}


 bool GameEngine::run (void){

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    if( TTF_Init() == -1)
        return false;
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return false;
    SDL_WM_SetCaption( "Capture the flag", NULL );

    if(loadFiles() == false)
        return 1;

    bool runmenu = true ;

    while(runmenu == true){
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        while(SDL_PollEvent(&Event)){

            if(Event.type == SDL_QUIT)
                runmenu = false;
            else  if(Event.type == SDL_MOUSEBUTTONDOWN){
                if( (x >= 456 && y >= 81 ) && (x <= 842 && y <= 131 )){
                    if(playGame() == false)
                        return 1;
                }
                else if( (x >= 456 && y >= 133 ) && (x <= 842 && y <= 183 )){
                     if(helpPage() == false)
                        return 1;
                }
                else if( (x >= 456 && y >= 185 ) && (x <= 842 && y <= 235 )){
                    runmenu = false;
                }

            }
        }
        blitSurface(0, 0, mainmenu , screen ,&screen->clip_rect );
        SDL_Flip(screen);
    }
    return 0;
 }
bool GameEngine::helpPage(){

    bool quit = false;
    while( quit == false ){
        startTimer();
        while( SDL_PollEvent( &Event ) ){
            switch (Event.type) {
            case SDL_QUIT: {
                return false;
                break;
            }
            case SDL_KEYDOWN:
                if(Event.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                    startTicks = 0;
                }
            }

        }

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        blitSurface(0, 0, howtoplay , screen ,&screen->clip_rect );
        SDL_Flip(screen);

        if( getTime()  < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - getTime() );

        }
        return true;



}
bool GameEngine::playGame(){

    int enmPos[11][2]={ {80 , 440},
                        {680 , 520},
                        {960 , 520},
                        {680, 1000},
                        {1040 , 920},
                        {1480 , 120},
                        {1600 , 120},
                        {1720 , 1080},
                        {1760 , 1080},
                        {2040 , 280},
                        {1920 , 520},



    };
    SDL_Color text = {0,0,0};
    Tile *tiles[ TOTAL_TILES ];
    Castle flag(2160, 120 , screen , &Camera , castle );
    Enemy *Enm[TOTAL_ENEMY];
    for( int i = 0 ; i < TOTAL_ENEMY ; i++){
            int x;
            if ((i % 2)==0)
                x = 2;
            else
                x = 1;
        Enm[i] = new Enemy(enmPos[i][0], enmPos[i][1] , x , screen , &Camera , enemy );
    }
    Hero player(screen , &Camera , hero, Enm , tiles,&flag);


    if(setTiles( tiles ) == false)
        return 1;

    int sTime = getTime();

    bool quit = false;
    bool dead = false;
    bool win = false;
    bool timesup = false;

    while( quit == false )
    {
        startTimer();
        if(player.getLives()==0){
            quit = true;
            dead = true;
            win = false;

        }
        if(player.flagCaptured()== true){
            quit = true;
            win = true;
            dead = false;

        }


        while( SDL_PollEvent( &Event ) )
        {
            switch (Event.type) {
            case SDL_QUIT: {
                quit = true;
                dead = false;
                win = false;
                return false;
                break;
            }
            case SDL_KEYDOWN:
                player.onKeyDown( &Event );
                if(Event.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                    dead = false;
                    win = false;
                    startTicks = 0;
                    Camera.x = 0;
                    Camera.y = 0;
                }

                break ;
            case SDL_KEYUP:   player.onKeyUp( &Event );   break ;
           }
        }
        player.move();
        for( int i = 0 ; i < TOTAL_ENEMY ; i++){
            Enm[i]->move();
        }

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        player.setCamera();
        for(int i = 0 ; i <TOTAL_TILES ; i ++ )
            tiles[ i ]->showTile();
        player.show();
        for( int i = 0 ; i < TOTAL_ENEMY ; i++){
            Enm[i]->show();
        }
        flag.showCastle();

           scroll = loadImage("scroll.png");

        if( scroll == NULL )
            return false;

        std::stringstream life;
        life << "Lives:" << player.getLives();
        score = TTF_RenderText_Solid( Ninja, life.str().c_str(), text );
        blitSurface(680 , 5 ,score , scroll , &score->clip_rect);
        blitSurface(0,0,scroll,screen , &scroll->clip_rect);

        int seconds , minutes;
        seconds =(( SDL_GetTicks() - sTime)/ 1000) % 60 ;
        minutes =(( SDL_GetTicks() - sTime)/ 1000) / 60 ;
        if(minutes == 3 && seconds == 0)
        {
            quit = true;
            startTicks = 0;
            timesup = true;
            win = false;
            dead = false;
        }

        std::stringstream time;
        time << "Time: " <<  2 - minutes << " min : "<< 59 -seconds<<" sec";
        timer = TTF_RenderText_Solid( Ninja, time.str().c_str(), text );
        blitSurface(60 , 5 ,timer , scroll , &timer->clip_rect);
        blitSurface(0,0,scroll,screen , &scroll->clip_rect);
        SDL_FreeSurface( timer );


        SDL_Flip(screen);

        if( getTime()  < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - getTime() );

        }
        if(dead == true){
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            blitSurface(0 , 0 , losingscreen ,  screen , &screen->clip_rect);
            SDL_Flip(screen);
            SDL_Delay(1000);
        }
        else if (win == true){
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            blitSurface(0 , 0 , winningscreen ,  screen , &screen->clip_rect);
            SDL_Flip(screen);
            SDL_Delay(1000);
        }
         else if (timesup == true){
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            blitSurface(0 , 0 , timeup ,  screen , &screen->clip_rect);
            SDL_Flip(screen);
            SDL_Delay(1000);
        }


        return true;

}

void GameEngine::startTimer(){
    startTicks = SDL_GetTicks();
}

int GameEngine::getTime(){
    return SDL_GetTicks()- startTicks ;
}


void GameEngine::cleanUp( )
{
    SDL_FreeSurface( hero );
    SDL_FreeSurface( enemy );
    SDL_FreeSurface( castle );
    SDL_FreeSurface( tileSheet );
    SDL_FreeSurface( mainmenu );
    SDL_FreeSurface( winningscreen );
    SDL_FreeSurface( losingscreen );
    SDL_FreeSurface( howtoplay );
    SDL_FreeSurface( timeup );
    for( int t = 0; t < TOTAL_TILES; t++ )
        delete tiles[ t ];
    delete tiles;
    SDL_Quit();
}


bool GameEngine::loadFiles(){

    Ninja = TTF_OpenFont("lastninja.ttf" ,30);

    hero = loadImage( "hero.png" );
    if( hero == NULL )
        return false;

    castle = loadImage("castle.png");
    if(castle== NULL)
        return false;

    enemy = loadImage( "enemy.png" );
    if( enemy == NULL )
        return false;

    tileSheet = loadImage( "sprite.png" );
    if( tileSheet == NULL )
        return false;

    mainmenu = loadImage("main1.png");
    if( mainmenu == NULL )
        return false;

    winningscreen = loadImage("win.png");
    if( winningscreen == NULL )
        return false;
    howtoplay = loadImage("instruction.png");
    if( howtoplay == NULL )
        return false;

    losingscreen = loadImage("lost.png");
    if( losingscreen == NULL )
        return false;

    timeup = loadImage("timeup.png");
    if( timeup == NULL )
        return false;
    return true;

}

SDL_Surface* GameEngine::loadImage( std::string filename )
{
    SDL_Surface* loadedImg = NULL;
    SDL_Surface* optimizedImg = NULL;
    loadedImg = IMG_Load( filename.c_str() );

    if( loadedImg != NULL )
    {
        optimizedImg = SDL_DisplayFormat( loadedImg );

        SDL_FreeSurface( loadedImg );
        if( optimizedImg != NULL )
            SDL_SetColorKey( optimizedImg, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImg->format, 0xFF, 0xFF, 0xFF ) );
    }
    return optimizedImg;
}


bool GameEngine::setTiles(Tile *tiles[]){
    int x = 0, y = 40;
    ifstream map( "tile.map" );

    if( map == NULL )
    {
        return false;
    }

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        int tileType = -1;

        map >> tileType;

        if( map.fail() == true )
        {
            map.close();
            return false;
        }

        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y, tileType , screen , &Camera , tileSheet);
        }
        else
        {
            map.close();
            return false;
        }

        x += TILE_WIDTH;

        if( x >= LEVEL_WIDTH )
        {
            x = 0;

            y += TILE_HEIGHT;
        }
    }

    map.close();

    return true;

}

void GameEngine::blitSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

