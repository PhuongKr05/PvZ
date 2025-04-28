#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

class Bullet {
private:
    SDL_Rect posRect;
    SDL_Renderer* rendererRef;
    bool destroyed = false;

public:
    Bullet(SDL_Renderer* renderer, int x, int y);
    void update();
    void render();
    void destroy();
    bool isDestroyed();

    const SDL_Rect& getRect() { return posRect; }
};

#endif
