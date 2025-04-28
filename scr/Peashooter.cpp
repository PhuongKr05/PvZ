#include "Peashooter.h"
#include "TextureManager.h"
#include "SoundManager.h"


Peashooter::Peashooter(SDL_Renderer* renderer, int x, int y, std::vector<Bullet*>& bullets)
    : rendererRef(renderer), bulletsRef(bullets) {
    texture = TextureManager::GetTexture("peashooter");
    posRect = { x, y, 60, 60 };
}

void Peashooter::update() {
    shootTimer++;
    if (shootTimer >= 80) {   // Diều chỉnh thời gian bắn ra đạn
        bulletsRef.push_back(new Bullet(rendererRef, posRect.x + 30, posRect.y + 20));
        SoundManager::PlaySound("shoot");
        shootTimer = 0;
    }
}


void Peashooter::render() {
    SDL_RenderCopy(rendererRef, texture, NULL, &posRect);
}

void Peashooter::takeDamage(int dmg) {
    health -= dmg;
}

bool Peashooter::isDestroyed() {
    return health <= 0;
}

