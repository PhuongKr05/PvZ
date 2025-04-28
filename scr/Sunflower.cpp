#include "Sunflower.h"
#include "TextureManager.h"

Sunflower::Sunflower(SDL_Renderer* renderer, int x, int y, std::vector<Sun*>& suns)
    : rendererRef(renderer), suns(suns), generateTimer(0) {
    texture = TextureManager::GetTexture("sunflower");
    posRect = { x, y, 60, 60 };
}

void Sunflower::update() {
    generateTimer++;
    if (generateTimer >= 200) {
        suns.push_back(new Sun(rendererRef, posRect.x + 10, posRect.y + 10));
        generateTimer = 0;
    }
}

void Sunflower::render() {
    SDL_RenderCopy(rendererRef, texture, NULL, &posRect);
}

void Sunflower::takeDamage(int dmg) {
    health -= dmg;
}

bool Sunflower::isDestroyed() {
    return health <= 0;
}

