#ifndef _GAME__H_
#define _GAME__H_

#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "button.h"
using namespace std;


struct Game{
    private:
        Graphics graphics;

        int score, bestScore;
        int x, y;
        int fieldSizeX, fieldSizeY;
        int choosenTileX, choosenTileY;
        int tileLeft, bombCount, gameMode, numberOfBombs;
        bool gameOver, isShovel, won;
        vector<vector<int>> bombField;
        vector<vector<char>> playersField;

        Button easyButton;
        Button normalButton;
        Button hardButton;
        Button quitButton;
        Button pauseButton;
        Button continueButton;
        Button shovelButton;
        Button flagButton;

        SDL_Texture* background;
        SDL_Texture* blurBackground;
        SDL_Texture* tileGrass;
        SDL_Texture* tileFlag;
        SDL_Texture* tileBomb;
        SDL_Texture* tile0;
        SDL_Texture* tile1;
        SDL_Texture* tile2;
        SDL_Texture* tile3;
        SDL_Texture* tile4;
        SDL_Texture* tile5;
        SDL_Texture* tile6;
        SDL_Texture* tile7;
        SDL_Texture* tile8;

        Sprite explode;
        const int explodeFrame = 15;
        const int explodeClips[15][4] = {
            {0,0,99,99},
            {100,0,99,99},
            {200,0,99,99},
            {300,0,99,99},
            {400,0,99,99},
            {0,100,99,99},
            {100,100,99,99},
            {200,100,99,99},
            {300,100,99,99},
            {400,100,99,99},
            {0,200,99,99},
            {100,200,99,99},
            {200,200,99,99},
            {300,200,99,99},
            {400,200,99,99},
        };

        TTF_Font* font;
        SDL_Texture* highScoreNumber;
        SDL_Texture* highScoreText;
        SDL_Texture* youWin;
        SDL_Texture* youLost;
        SDL_Texture* toContinue;
        SDL_Texture* newHighScoreText;
        SDL_Rect textDest;

        Mix_Chunk* buttonSound;
        Mix_Chunk* diggingSound;
        Mix_Chunk* placingSound;
        Mix_Chunk* explodeSound;
        Mix_Chunk* winningSound;
        Mix_Chunk* losingSound;

    public:
        char* charHighScore();
        int lastHighScore();
        void newHighScore();
        Game();
        void waitUntilKeyPressed();
        void getClickPosition();

        void menuScene();
        int menuOption();

        void generateNewGame();
        void resetHighScoreNumber();
        void clearBlankTile(int Tx, int Ty);
        void printPlayersField();
        void inGameScene();
        bool ifChooseATile();
        int inGameOption();
        void prepareExplosion();
        void updatePlayersField();

        void pauseScene();
        int pauseOption();

        void endGameScene();

        void run();

        ~Game();
};


#endif // _GAME__H_
