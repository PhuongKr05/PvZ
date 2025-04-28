#include "Walnut.h"
#include "TextureManager.h"

Walnut::Walnut(SDL_Renderer* renderer, int x, int y) {
    rendererRef = renderer;
    texture = TextureManager::GetTexture("walnut"); 
    posRect = { x + 5, y + 5, 70, 70 };   
    health = 21;   // Tổng máu
}

void Walnut::update() {
    if (health <= 10 && health > 5) {
        texture = TextureManager::GetTexture("walnut_cracked1");   
    } 
    else if (health <= 5 && health > 0) {
        texture = TextureManager::GetTexture("walnut_cracked2");   
    }
}

void Walnut::render() {
    SDL_RenderCopy(rendererRef, texture, NULL, &posRect);
}

void Walnut::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

bool Walnut::isDestroyed() {
    return health <= 0;
}

PlantType Walnut::getType() { 
    return WALNUT; 
}

const SDL_Rect& Walnut::getRect() {
    return posRect;
}
