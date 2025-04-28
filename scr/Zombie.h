#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SDL.h>

class Zombie {
private:
    SDL_Texture* texture;
    SDL_Renderer* rendererRef;
    SDL_Rect posRect;
    int health;
    bool isStopped;

    int attackTimer = 0;
    const int attackCooldown = 60;   // Điều chỉnh tốc độ zombie ăn cây

public:
    Zombie(SDL_Renderer* renderer, int x, int y);
    void update();
    void render();
    void takeDamage(int dmg);
    bool isDead();
    bool reachHouse();
    const SDL_Rect& getRect();
    void stop() { isStopped = true; }
    void move() { isStopped = false; }

    bool tryAttack();   //  Kiểm soát Zombie tấn công
};

#endif
