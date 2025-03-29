#include <iostream>
#include <fstream>
#include "graphics.h"
#include "defs.h"

void Graphics::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* Graphics::createWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    return window;
}

SDL_Renderer* Graphics::createRenderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void Graphics::TTFInit(){
    if (TTF_Init() == -1)
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
}

void Graphics::MixerInit(){
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
}

void Graphics::prepareScene(SDL_Texture * background){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
    }

void Graphics::presentScene(){
        SDL_RenderPresent(renderer);
    }

SDL_Texture* Graphics::loadTexture(const char *filename){
   // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y){
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

TTF_Font* Graphics::loadFont(const char* path, int size){
    TTFInit();
    TTF_Font* gFont = TTF_OpenFont( path, size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor){
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }

    SDL_FreeSurface( textSurface );
    return texture;
}

Mix_Music* Graphics::loadMusic(const char* path){
    MixerInit();
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    return gMusic;
}

void Graphics::play(Mix_Music *gMusic){
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0) Mix_PlayMusic( gMusic, -1 );
    else if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
}

Mix_Chunk* Graphics::loadSound(const char* path){
    MixerInit();
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
}

void Graphics::play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) Mix_PlayChannel( -1, gChunk, 0 );
}

void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y){
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, texture, src, &dest);
}


void Graphics::quit(){
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

char* Graphics::charBestScore(){
    std::ifstream fin;
    fin.open("assets\\best_score.txt");
    char bestScore[10];
    fin >> bestScore;
    fin.close();
    char* score = bestScore;
    return score;
}

void Graphics::destroyTexture(){
        SDL_DestroyTexture( background );
        background = NULL;
        SDL_DestroyTexture( newGameButton );
        newGameButton = NULL;
        SDL_DestroyTexture( quitButton );
        quitButton = NULL;
        SDL_DestroyTexture( flag );
        flag = NULL;
        SDL_DestroyTexture( tileGrass );
        tileGrass = NULL;
        SDL_DestroyTexture( tileFlag );
        tileFlag = NULL;
        SDL_DestroyTexture( tile0 );
        tile0 = NULL;
        SDL_DestroyTexture( tile1 );
        tile1 = NULL;
        SDL_DestroyTexture( tile2 );
        tile2 = NULL;
        SDL_DestroyTexture( tile3 );
        tile3 = NULL;
        SDL_DestroyTexture( tile4 );
        tile4 = NULL;
        SDL_DestroyTexture( tile5 );
        tile5 = NULL;
        SDL_DestroyTexture( tile6 );
        tile6 = NULL;
        SDL_DestroyTexture( tile7 );
        tile7 = NULL;
        SDL_DestroyTexture( tile8 );
        tile8 = NULL;
        TTF_CloseFont( font );
        font = NULL;
        SDL_DestroyTexture( bestScoreNumber );
        bestScoreNumber = NULL;
        SDL_DestroyTexture( bestScoreText );
        bestScoreText = NULL;
        SDL_DestroyTexture( blurBackground );
        blurBackground = NULL;
        SDL_DestroyTexture( shovelActionButton );
        shovelActionButton = NULL;
        SDL_DestroyTexture( flagActionButton );
        flagActionButton = NULL;
        SDL_DestroyTexture( continueButton );
        continueButton = NULL;
        SDL_DestroyTexture( newHighScore );
        newHighScore = NULL;
        SDL_DestroyTexture( explodeSprite );
        explodeSprite = NULL;
        SDL_DestroyTexture( tileBomb );
        tileBomb = NULL;
        Mix_FreeChunk( buttonSound );
        buttonSound = NULL;
        Mix_FreeChunk( diggingSound );
        diggingSound = NULL;
        Mix_FreeChunk( placingSound );
        placingSound = NULL;
        Mix_FreeChunk( explodeSound );
        explodeSound = NULL;
        Mix_FreeChunk( winningSound );
        winningSound = NULL;
        Mix_FreeChunk( losingSound );
        losingSound = NULL;
    }

void Sprite::init(SDL_Texture* _texture, int frames, const int _clips [][4]){
    texture = _texture;
    SDL_Rect clip;
    for (int i = 0; i < frames; i++){
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
}

void Sprite::tick(){
    currentFrame = (currentFrame + 1) % clips.size();
}

const SDL_Rect* Sprite::getCurrentClip() const{
    return &(clips[currentFrame]);
}

void Graphics::renderSprite(int x, int y, const Sprite& sprite){
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
}
