#ifndef PLANT_H
#define PLANT_H

#include <SDL.h>

enum PlantType { NONE, PEASHOOTER, SUNFLOWER, WALNUT };

class Plant {
protected:
    SDL_Rect posRect = { 0, 0, 0, 0 };   
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void takeDamage(int dmg) = 0;
    virtual bool isDestroyed() = 0;
    virtual PlantType getType() = 0;
    virtual const SDL_Rect& getRect() { return posRect; }
    virtual ~Plant() {}
};

#endif
