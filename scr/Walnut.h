#ifndef WALNUT_H
#define WALNUT_H

#include "Plant.h"

class Walnut : public Plant {
private:
    SDL_Texture* texture;
    SDL_Renderer* rendererRef;
    SDL_Rect posRect;
    int health;

public:
    Walnut(SDL_Renderer* renderer, int x, int y);
    void update() override;
    void render() override;
    void takeDamage(int dmg) override;
    bool isDestroyed() override;
    PlantType getType() override;
    const SDL_Rect& getRect() override;
};


#endif
