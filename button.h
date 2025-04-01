#ifndef _BUTTON__H_
#define _BUTTON__H_

#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

class Button{
    private:
        SDL_Rect rect;
        SDL_Texture* buttonTexture;
        Mix_Chunk* buttonSound;
    public:
        void initButton(SDL_Texture* image, Mix_Chunk* sound, int x, int y);
        bool isPressed(Graphics graphics, int x, int y);
        void render(Graphics graphics);
        ~Button();
};


#endif // _BUTTON__H_
