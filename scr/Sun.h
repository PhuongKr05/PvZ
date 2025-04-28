#ifndef SUN_H
#define SUN_H

#include <SDL.h>

class Sun {
private:
    SDL_Renderer* rendererRef;
    SDL_Rect posRect;
    bool collected = false;
public:
    Sun(SDL_Renderer* renderer, int x, int y);
    void update();
    void render();
    bool isCollected() { return collected; }
    bool isClicked(int mouseX, int mouseY);
};

#endif
