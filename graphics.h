#ifndef _GRAPHICS__H_
#define _GRAPHICS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "defs.h"
#include "sprite.h"


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

    SDL_Window *window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer *renderer =createRenderer(window);

    void renderSprite(int x, int y, const Sprite& sprite);
};

#endif // _GRAPHICS__H_
