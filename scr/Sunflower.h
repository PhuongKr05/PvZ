#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "Plant.h"
#include "Sun.h"
#include <vector>

class Sunflower : public Plant {
private:
    SDL_Texture* texture;
    SDL_Renderer* rendererRef;
    std::vector<Sun*>& suns;
    int generateTimer;
    int health = 5;  //Máu cho Sunflower

public:
    Sunflower(SDL_Renderer* renderer, int x, int y, std::vector<Sun*>& suns);
    void update() override;
    void render() override;
    void takeDamage(int dmg) override;
    bool isDestroyed() override;
    PlantType getType() override { return SUNFLOWER; }
};

#endif
