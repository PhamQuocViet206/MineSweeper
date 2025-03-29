//#ifndef _TEXTURE__H_
//#define _TEXTURE__H_
//
//#include "graphics.h"
//
//struct Texture{
//    SDL_Texture* background = loadTexture("assets\\background.png");
//    SDL_Texture* newGameButton = loadTexture("assets\\new_game_button.png");
//    SDL_Texture* quitButton = loadTexture("assets\\quit_button.png");
//    SDL_Texture* flag = loadTexture("assets\\flag.png");
//    SDL_Texture* tileGrass = loadTexture("assets\\tile_grass.png");
//    SDL_Texture* tileFlag = loadTexture("assets\\tile_flag.png");
//    SDL_Texture* tile0 = loadTexture("assets\\tile_0.png");
//    SDL_Texture* tile1 = loadTexture("assets\\tile_1.png");
//    SDL_Texture* tile2 = loadTexture("assets\\tile_2.png");
//    SDL_Texture* tile3 = loadTexture("assets\\tile_3.png");
//    SDL_Texture* tile4 = loadTexture("assets\\tile_4.png");
//    SDL_Texture* tile5 = loadTexture("assets\\tile_5.png");
//    SDL_Texture* tile6 = loadTexture("assets\\tile_6.png");
//    SDL_Texture* tile7 = loadTexture("assets\\tile_7.png");
//    SDL_Texture* tile8 = loadTexture("assets\\tile_8.png");
//    SDL_Texture* blurBackground = loadTexture("assets\\blur_background.png");
//    SDL_Texture* pauseButton = loadTexture("assets\\pause_button.png");
//    SDL_Texture* shovelActionButton = loadTexture("assets\\shovel_action_button.png");
//    SDL_Texture* flagActionButton = loadTexture("assets\\flag_action_button.png");
//    SDL_Texture* continueButton = loadTexture("assets\\continue_button.png");
//
//    TTF_Font* font = loadFont("assets\\light-arial.ttf", 50);
//    SDL_Color color = {0, 0, 0, 0};
//
//    SDL_Texture* bestScoreNumber = renderText(charBestScore(), font, color);
//    SDL_Texture* bestScoreText = renderText("Best score: ", font, color);
//    SDL_Texture* youWin = renderText("You WIN!", font, {0, 255, 0, 0});
//    SDL_Texture* youLost = renderText("You lost...", font, {255, 0, 0, 0});
//    SDL_Texture* toContinue = renderText("Click anywhere to continue.", font, color);
//    SDL_Texture* newHighScore = renderText("NEW HIGH SCORE!!!", font, {0, 255, 0, 0});
//
//    SDL_Rect textDest;
//    int dummy = SDL_QueryTexture(bestScoreText, NULL, NULL, &textDest.w, &textDest.h);
//
//    void destroyTexture(){
//        SDL_DestroyTexture( background );
//        background = NULL;
//        SDL_DestroyTexture( newGameButton );
//        newGameButton = NULL;
//        SDL_DestroyTexture( quitButton );
//        quitButton = NULL;
//        SDL_DestroyTexture( flag );
//        flag = NULL;
//        SDL_DestroyTexture( tileGrass );
//        tileGrass = NULL;
//        SDL_DestroyTexture( tileFlag );
//        tileFlag = NULL;
//        SDL_DestroyTexture( tile0 );
//        tile0 = NULL;
//        SDL_DestroyTexture( tile1 );
//        tile1 = NULL;
//        SDL_DestroyTexture( tile2 );
//        tile2 = NULL;
//        SDL_DestroyTexture( tile3 );
//        tile3 = NULL;
//        SDL_DestroyTexture( tile4 );
//        tile4 = NULL;
//        SDL_DestroyTexture( tile5 );
//        tile5 = NULL;
//        SDL_DestroyTexture( tile6 );
//        tile6 = NULL;
//        SDL_DestroyTexture( tile7 );
//        tile7 = NULL;
//        SDL_DestroyTexture( tile8 );
//        tile8 = NULL;
//        TTF_CloseFont( font );
//        font = NULL;
//        SDL_DestroyTexture( bestScoreNumber );
//        bestScoreNumber = NULL;
//        SDL_DestroyTexture( bestScoreText );
//        bestScoreText = NULL;
//        SDL_DestroyTexture( blurBackground );
//        blurBackground = NULL;
//        SDL_DestroyTexture( shovelActionButton );
//        shovelActionButton = NULL;
//        SDL_DestroyTexture( flagActionButton );
//        flagActionButton = NULL;
//        SDL_DestroyTexture( continueButton );
//        continueButton = NULL;
//        SDL_DestroyTexture( newHighScore );
//        newHighScore = NULL;
//    }
//
//};
//
//#endif // _TEXTURE__H_
