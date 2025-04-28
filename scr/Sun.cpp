#include "Sun.h"
#include "TextureManager.h"

Sun::Sun(SDL_Renderer* renderer, int x, int y) {
    rendererRef = renderer;
    posRect = { x, y, 40, 40 };
}

void Sun::update() {
    posRect.y += 1;  
}

void Sun::render() {
    SDL_RenderCopy(rendererRef, TextureManager::GetTexture("sun"), NULL, &posRect);
}

bool Sun::isClicked(int mouseX, int mouseY) {
    SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };
    if (SDL_HasIntersection(&posRect, &mouseRect)) {
        collected = true;
        return true;
    }
    return false;
}
