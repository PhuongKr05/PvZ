#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(SDL_Renderer* renderer, int x, int y)
    : rendererRef(renderer) {
    posRect = { x, y, 20, 20 };   
}

void Bullet::update() {
    posRect.x += 5;   
    if (posRect.x > 900) {   
        destroy();
    }
}
void Bullet::render() {
    SDL_RenderCopy(rendererRef, TextureManager::GetTexture("bullet"), NULL, &posRect);
}


void Bullet::destroy() {
    destroyed = true;
}

bool Bullet::isDestroyed() {
    return destroyed;
}
