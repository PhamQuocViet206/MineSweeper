#ifndef _SPRITE__H_
#define _SPRITE__H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct Sprite {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;
    void init(SDL_Texture* _texture, int frames, const int _clips [][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
};

#endif // _SPRITE__H_
