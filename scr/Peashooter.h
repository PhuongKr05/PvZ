#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "Plant.h"
#include "Bullet.h"
#include <vector>

class Peashooter : public Plant {
private:
    SDL_Texture* texture;
    SDL_Renderer* rendererRef;
    std::vector<Bullet*>& bulletsRef;

    int shootTimer = 0;
    int health = 3;

public:
    Peashooter(SDL_Renderer* renderer, int x, int y, std::vector<Bullet*>& bullets);
    void update() override;
    void render() override;
    void takeDamage(int dmg) override;
    bool isDestroyed() override;
    PlantType getType() override { return PEASHOOTER; }
    const SDL_Rect& getRect() override { return posRect; }
};

#endif
