#include "Zombie.h"
#include "TextureManager.h"

Zombie::Zombie(SDL_Renderer* renderer, int x, int y) {
    rendererRef = renderer;
    texture = TextureManager::GetTexture("zombie_healthy");
    posRect = { x, y, 60, 80 };
    health = 5;
    isStopped = false;
}

void Zombie::update() {
    if (!isStopped) posRect.x -= 1;
}

void Zombie::render() {
    SDL_RenderCopy(rendererRef, texture, NULL, &posRect);
}

void Zombie::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 2) { // khi yeus máu chuyển sang dạng bị thương
        texture = TextureManager::GetTexture("zombie_injured");
    }
}

bool Zombie::isDead() {
    return health <= 0;
}

bool Zombie::reachHouse() {
    return posRect.x <= 0;
}

const SDL_Rect& Zombie::getRect() {
    return posRect;
}
bool Zombie::tryAttack() {
    attackTimer++;
    if (attackTimer >= attackCooldown) {
        attackTimer = 0;

        return true;  
    }
    return false;
}

