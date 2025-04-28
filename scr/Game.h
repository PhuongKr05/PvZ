#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "Grid.h"
#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Sun.h"
#include <vector>
#include <string>

struct Level {
    int totalZombie = 0;
    int spawnRate = 0;
    int initialSun = 0;
    std::vector<std::string> zombieTypes;
};



class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void loadLevel(int lv);
    bool running();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    bool isRunning, isStartScreen, isWin, isLose;
    int sunCount, spawnTimer, spawnInterval, totalZombieTarget, totalZombiesSpawned;
    int currentLevel;

    Grid grid;
    std::vector<Plant*> plants;
    std::vector<Zombie*> zombies;
    std::vector<Bullet*> bullets;
    std::vector<Sun*> suns;

    PlantType selectedPlant;

    // Biến thời gain hồi cho cây 
    int peashooterCooldown = 0;
    int sunflowerCooldown = 0;
    int walnutCooldown = 0;

    const int PEASHOOTER_COOLDOWN_TIME = 300;   // ~5 giây
    const int SUNFLOWER_COOLDOWN_TIME = 200;    // ~3.3 giây
    const int WALNUT_COOLDOWN_TIME = 500;       // ~8.3 giây

    //Điều khiển Xẻng 
    bool isShovelSelected = false;

    // Sun tự nhiên 
    int naturalSunTimer = 0;
    const int naturalSunInterval = 500;

    //Cảnh báo & Level
    bool showWarning;
    int warningTimer;
    std::vector<Level> levels;    
    Level currentLevelData;        
};

#endif
