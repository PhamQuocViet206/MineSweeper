#include "button.h"

void Button::initButton(SDL_Texture* image, Mix_Chunk* sound, int x, int y){
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(image, NULL, NULL, &rect.w, &rect.h);
    buttonTexture = image;
    buttonSound = sound;
}

Button::~Button(){
    SDL_DestroyTexture(buttonTexture);
    buttonTexture = NULL;
}

bool Button::isPressed(Graphics graphics, int x, int y){
    if(x>=rect.x&&x<=rect.x+rect.w-1&&y>=rect.y&&y<=rect.y+rect.h-1){
        graphics.play(buttonSound);
        return true;
    }
    return false;
}

void Button::render(Graphics graphics){
    graphics.renderTexture(buttonTexture,rect.x,rect.y);
}
