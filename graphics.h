#ifndef _GRAPHICS__H_
#define _GRAPHICS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "defs.h"

struct Sprite {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
};

struct Graphics{

    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* createWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void TTFInit();
    void MixerInit();

    void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);

    Mix_Music *loadMusic(const char* path);
    void play(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);

    void quit();
    char* charBestScore();

    SDL_Window *window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper Replica");
    SDL_Renderer *renderer =createRenderer(window);

    SDL_Texture* background = loadTexture("assets\\background.png");
    SDL_Texture* newGameButton = loadTexture("assets\\new_game_button.png");
    SDL_Texture* quitButton = loadTexture("assets\\quit_button.png");
    SDL_Texture* flag = loadTexture("assets\\flag.png");
    SDL_Texture* tileGrass = loadTexture("assets\\tile_grass.png");
    SDL_Texture* tileFlag = loadTexture("assets\\tile_flag.png");
    SDL_Texture* tileBomb = loadTexture("assets\\tile_bomb.png");
    SDL_Texture* tile0 = loadTexture("assets\\tile_0.png");
    SDL_Texture* tile1 = loadTexture("assets\\tile_1.png");
    SDL_Texture* tile2 = loadTexture("assets\\tile_2.png");
    SDL_Texture* tile3 = loadTexture("assets\\tile_3.png");
    SDL_Texture* tile4 = loadTexture("assets\\tile_4.png");
    SDL_Texture* tile5 = loadTexture("assets\\tile_5.png");
    SDL_Texture* tile6 = loadTexture("assets\\tile_6.png");
    SDL_Texture* tile7 = loadTexture("assets\\tile_7.png");
    SDL_Texture* tile8 = loadTexture("assets\\tile_8.png");
    SDL_Texture* blurBackground = loadTexture("assets\\blur_background.png");
    SDL_Texture* pauseButton = loadTexture("assets\\pause_button.png");
    SDL_Texture* shovelActionButton = loadTexture("assets\\shovel_action_button.png");
    SDL_Texture* flagActionButton = loadTexture("assets\\flag_action_button.png");
    SDL_Texture* continueButton = loadTexture("assets\\continue_button.png");

    SDL_Texture* explodeSprite = loadTexture("assets\\explode_sprite.png");
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

    TTF_Font* font = loadFont("assets\\light-arial.ttf", 50);
    SDL_Color color = {0, 0, 0, 0};
    SDL_Texture* bestScoreNumber = renderText(charBestScore(), font, color);
    SDL_Texture* bestScoreText = renderText("Best score: ", font, color);
    SDL_Texture* youWin = renderText("You WIN!", font, {0, 255, 0, 0});
    SDL_Texture* youLost = renderText("You lost...", font, {255, 0, 0, 0});
    SDL_Texture* toContinue = renderText("Click anywhere to continue.", font, color);
    SDL_Texture* newHighScore = renderText("NEW HIGH SCORE!!!", font, {0, 255, 0, 0});

    Mix_Chunk* buttonSound = loadSound("assets\\button_sound.wav");
    Mix_Chunk* diggingSound = loadSound("assets\\digging_sound.wav");
    Mix_Chunk* placingSound = loadSound("assets\\placing_sound.wav");
    Mix_Chunk* explodeSound = loadSound("assets\\explode_sound.wav");
    Mix_Chunk* winningSound = loadSound("assets\\winning_sound.wav");
    Mix_Chunk* losingSound = loadSound("assets\\losing_sound.wav");

    SDL_Rect textDest;
    int dummy = SDL_QueryTexture(bestScoreText, NULL, NULL, &textDest.w, &textDest.h);

    void destroyTexture();
    void renderSprite(int x, int y, const Sprite& sprite);
};

#endif // _GRAPHICS__H_
