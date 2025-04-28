#include "Game.h"
#include "TextureManager.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Walnut.h"
#include "Zombie.h"
#include "SoundManager.h"
#include <algorithm>
#include <ctime>

Game::Game() {
    isRunning = true;
    isStartScreen = true;
    isWin = false;
    isLose = false;

    selectedPlant = NONE;
    isShovelSelected = false;

    font = nullptr;
    renderer = nullptr;
    window = nullptr;

    sunCount = 0;
    spawnTimer = 0;
    spawnInterval = 0;
    totalZombiesSpawned = 0;
    totalZombieTarget = 0;

    showWarning = false;
    warningTimer = 0;

    currentLevel = 0;

    // Khởi tạo levels
    levels = {
        {10, 300, 250, {"normal"}},
        {15, 250, 275, {"normal", "conehead"}},
        {20, 200, 300, {"normal", "conehead", "buckethead"}}
    };
}


Game::~Game() {
    clean();
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SoundManager::Init();
    SoundManager::PlayMusic("bgm");

    window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    TextureManager::SetRenderer(renderer);
    font = TTF_OpenFont("font.ttf", 24);

    // Load texture cơ bản
    TextureManager::LoadTexture("background", "images/Frontyard.png");
    TextureManager::LoadTexture("item_bar", "images/Item_Bar.png");
    TextureManager::LoadTexture("sun_bar", "images/sun_bar.png");
    TextureManager::LoadTexture("shovel", "images/Shovel.png");
    TextureManager::LoadTexture("shovel_selected", "images/Shovel2.png");


    // Load icon cây 
    TextureManager::LoadTexture("icon_peashooter", "images/icon_peashooter_100.png");
    TextureManager::LoadTexture("icon_peashooter_dim", "images/icon_peashooter_100_dim.png");
    TextureManager::LoadTexture("icon_sunflower", "images/icon_sunflower.png");
    TextureManager::LoadTexture("icon_sunflower_dim", "images/icon_sunflower_dim.png");
    TextureManager::LoadTexture("icon_walnut", "images/icon_walnut.png");
    TextureManager::LoadTexture("icon_walnut_dim", "images/icon_walnut_dim.png");
    TextureManager::LoadTexture("peashooter", "images/Peashooter.png");
    TextureManager::LoadTexture("sunflower", "images/Sunflower.png");
    TextureManager::LoadTexture("walnut", "images/Wallnut_body.png");
    TextureManager::LoadTexture("walnut_cracked1", "images/Wallnut_cracked1.png");
    TextureManager::LoadTexture("walnut_cracked2", "images/Wallnut_cracked2.png");
    TextureManager::LoadTexture("bullet", "images/pea.png");
    TextureManager::LoadTexture("sun", "images/sun.png");
    TextureManager::LoadTexture("zombie_healthy", "images/Zombie_healthy.png");
    TextureManager::LoadTexture("zombie_injured", "images/Zombie_Injured.png");
    TextureManager::LoadTexture("start_screen", "images/Starting_Screen.png");
    TextureManager::LoadTexture("game_completed", "images/game_completed.png");
    TextureManager::LoadTexture("lose", "images/Losing_Message.png");
    TextureManager::LoadTexture("next_level", "images/next_level.png");
    loadLevel(currentLevel);
}

void Game::loadLevel(int lv) {
    if (lv >= 0 && lv < levels.size()) {
        currentLevelData = levels[lv];
        sunCount = currentLevelData.initialSun;
        spawnInterval = currentLevelData.spawnRate;
        totalZombieTarget = currentLevelData.totalZombie;
        totalZombiesSpawned = 0;
        spawnTimer = 0;

        isWin = false;
        isLose = false;
        selectedPlant = NONE;
        isShovelSelected = false;

        plants.clear();
        zombies.clear();
        bullets.clear();
        suns.clear();
        grid.reset();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_KEYDOWN:
        if (isStartScreen && event.key.keysym.sym == SDLK_RETURN) {
            isStartScreen = false;
            loadLevel(currentLevel);
        }
        else if (isWin && event.key.keysym.sym == SDLK_RETURN) {
            if (currentLevel < levels.size() - 1) {
                currentLevel++;
                loadLevel(currentLevel);
            }
            else {
                isStartScreen = true;
                currentLevel = 0;
            }
        }
        else if (isLose && event.key.keysym.sym == SDLK_RETURN) {
            loadLevel(currentLevel);
        }
        else if (event.key.keysym.sym == SDLK_ESCAPE) {
            selectedPlant = NONE;
            isShovelSelected = false;
        }
        //Chọn cây bằng bàn phím
        else if (event.key.keysym.sym == SDLK_1 && peashooterCooldown == 0) {
            selectedPlant = PEASHOOTER;
            isShovelSelected = false;
        }
        else if (event.key.keysym.sym == SDLK_2 && sunflowerCooldown == 0) {
            selectedPlant = SUNFLOWER;
            isShovelSelected = false;
        }
        else if (event.key.keysym.sym == SDLK_3 && walnutCooldown == 0) {
            selectedPlant = WALNUT;
            isShovelSelected = false;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Chọn cây bằng chuột 
        if (y >= 20 && y <= 80) {
            if (x >= 50 && x <= 110 && peashooterCooldown == 0) {
                selectedPlant = PEASHOOTER;
                isShovelSelected = false;
            }
            else if (x >= 120 && x <= 180 && sunflowerCooldown == 0) {
                selectedPlant = SUNFLOWER;
                isShovelSelected = false;
            }
            else if (x >= 190 && x <= 250 && walnutCooldown == 0) {
                selectedPlant = WALNUT;
                isShovelSelected = false;
            }
        }

        // Chọn xẻng
        if (x >= 20 && x <= 80 && y >= 520 && y <= 580) {
            isShovelSelected = true;
            selectedPlant = NONE;
            break;
        }

        // Dùng xẻng đào cây
        if (isShovelSelected) {
            int col = (x - 200) / Grid::CELL_WIDTH;
            int row = (y - 100) / Grid::CELL_HEIGHT;
            if (col >= 0 && col < Grid::COLS && row >= 0 && row < Grid::ROWS) {
                if (grid.cells[row][col].hasPlant) {
                    auto it = std::find_if(plants.begin(), plants.end(), [&](Plant* p) {
                        return p->getRect().x == grid.cells[row][col].x && p->getRect().y == grid.cells[row][col].y;
                        });
                    if (it != plants.end()) {
                        delete* it;
                        plants.erase(it);
                        grid.cells[row][col].hasPlant = false;
                        SoundManager::PlaySound("shovel");
                    }
                }
            }
            isShovelSelected = false;
            break;
        }

        // Thu thập Sun
        for (auto s : suns) {
            if (!s->isCollected() && s->isClicked(x, y)) {
                sunCount += 25;
                SoundManager::PlaySound("sun");
            }
        }

        // Trồng cây
        if (y >= 100 && x >= 200) {
            int col = (x - 200) / Grid::CELL_WIDTH;
            int row = (y - 100) / Grid::CELL_HEIGHT;

            if (col >= 0 && col < Grid::COLS && row >= 0 && row < Grid::ROWS) {
                if (!grid.cells[row][col].hasPlant) {
                    int posX = grid.cells[row][col].x;
                    int posY = grid.cells[row][col].y;

                    if (selectedPlant == PEASHOOTER && sunCount >= 100) {
                        plants.push_back(new Peashooter(renderer, posX, posY, bullets));
                        sunCount -= 100;
                        peashooterCooldown = PEASHOOTER_COOLDOWN_TIME;
                        grid.cells[row][col].hasPlant = true;
                    }
                    else if (selectedPlant == SUNFLOWER && sunCount >= 50) {
                        plants.push_back(new Sunflower(renderer, posX, posY, suns));
                        sunCount -= 50;
                        sunflowerCooldown = SUNFLOWER_COOLDOWN_TIME;
                        grid.cells[row][col].hasPlant = true;
                    }
                    else if (selectedPlant == WALNUT && sunCount >= 50) {
                        plants.push_back(new Walnut(renderer, posX, posY));
                        sunCount -= 50;
                        walnutCooldown = WALNUT_COOLDOWN_TIME;
                        grid.cells[row][col].hasPlant = true;
                    }
                }
            }
        }
        break;
    }
}




void Game::update() {
    if (isStartScreen || isWin || isLose) return;

    for (auto p : plants) p->update();
    for (auto b : bullets) b->update();
    for (auto z : zombies) z->update();
    for (auto s : suns) s->update();

    // Va chạm đạn - zombie
    for (auto b : bullets) {
        for (auto z : zombies) {
            if (!b->isDestroyed() && !z->isDead() && SDL_HasIntersection(&b->getRect(), &z->getRect())) {
                z->takeDamage(1);
                b->destroy();
            }
        }
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) {
        if (b->isDestroyed()) { delete b; return true; }
        return false;
        }), bullets.end());

    // Zombie ăn cây
    for (auto z : zombies) {
        bool blocked = false;
        for (auto p : plants) {
            if (SDL_HasIntersection(&z->getRect(), &p->getRect())) {
                blocked = true;
                if (z->tryAttack()) {
                    p->takeDamage(1);
                }
                break;
            }
        }
        if (blocked) z->stop();
        else z->move();
    }

    plants.erase(std::remove_if(plants.begin(), plants.end(), [&](Plant* p) {
        if (p->isDestroyed()) {
            grid.cells[(p->getRect().y - 100) / Grid::CELL_HEIGHT][(p->getRect().x - 200) / Grid::CELL_WIDTH].hasPlant = false;
            delete p;
            return true;
        }
        return false;
        }), plants.end());

    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [](Zombie* z) {
        if (z->isDead()) { delete z; return true; }
        return false;
        }), zombies.end());

    for (auto z : zombies) {
        if (z->reachHouse()) {
            isLose = true;
            return;
        }
    }

    if (totalZombiesSpawned >= totalZombieTarget && zombies.empty()) {
        isWin = true;
        return;
    }

    spawnTimer++;
    if (spawnTimer >= spawnInterval && totalZombiesSpawned < totalZombieTarget) {
        int lane = rand() % Grid::ROWS;
        int zombieY = grid.cells[lane][0].y;
        zombies.push_back(new Zombie(renderer, 900, zombieY));
        totalZombiesSpawned++;
        spawnTimer = 0;
    }

    // Sinh sun tự nhiên
    naturalSunTimer++;
    if (naturalSunTimer >= naturalSunInterval) {
        int randomX = 200 + rand() % 500;
        suns.push_back(new Sun(renderer, randomX, 0));
        naturalSunTimer = 0;
    }

    // Giảm hồi chiêu 
    if (peashooterCooldown > 0) peashooterCooldown--;
    if (sunflowerCooldown > 0) sunflowerCooldown--;
    if (walnutCooldown > 0) walnutCooldown--;
}




void Game::render() {
    SDL_RenderClear(renderer);

    if (isStartScreen) {
        SDL_RenderCopy(renderer, TextureManager::GetTexture("start_screen"), NULL, NULL);
        SDL_RenderPresent(renderer);
        return;
    }


    SDL_RenderCopy(renderer, TextureManager::GetTexture("background"), NULL, NULL);
    SDL_Rect itemBarRect = { 0, 0, 900, 100 };
    SDL_RenderCopy(renderer, TextureManager::GetTexture("item_bar"), NULL, &itemBarRect);

    SDL_Rect peaIcon = { 50, 20, 60, 60 };
    SDL_Rect sunIcon = { 120, 20, 60, 60 };
    SDL_Rect walnutIcon = { 190, 20, 60, 60 };

    // Peashooter 
    if (peashooterCooldown > 0)
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_peashooter_dim"), NULL, &peaIcon);
    else
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_peashooter"), NULL, &peaIcon);
    if (selectedPlant == PEASHOOTER && peashooterCooldown == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &peaIcon);
    }

    // Sunflower 
    if (sunflowerCooldown > 0)
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_sunflower_dim"), NULL, &sunIcon);
    else
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_sunflower"), NULL, &sunIcon);
    if (selectedPlant == SUNFLOWER && sunflowerCooldown == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &sunIcon);
    }

    // Walnut 
    if (walnutCooldown > 0)
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_walnut_dim"), NULL, &walnutIcon);
    else
        SDL_RenderCopy(renderer, TextureManager::GetTexture("icon_walnut"), NULL, &walnutIcon);
    if (selectedPlant == WALNUT && walnutCooldown == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &walnutIcon);
    }

    // Shovel
    if (isShovelSelected) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect shovelFollow = { mouseX - 20, mouseY - 20, 40, 40 };
        SDL_RenderCopy(renderer, TextureManager::GetTexture("shovel_selected"), NULL, &shovelFollow);
    }
    else {
        SDL_Rect shovelRect = { 20, 520, 60, 60 };
        SDL_RenderCopy(renderer, TextureManager::GetTexture("shovel"), NULL, &shovelRect);
    }

    grid.renderGridHighlight(renderer, selectedPlant);

    for (auto p : plants) p->render();
    for (auto b : bullets) b->render();
    for (auto z : zombies) z->render();
    for (auto s : suns) if (!s->isCollected()) s->render();

    SDL_Rect sunBarRect = { 700, 20, 150, 50 };
    SDL_RenderCopy(renderer, TextureManager::GetTexture("sun_bar"), NULL, &sunBarRect);

    SDL_Color textColor = { 0, 0, 0 };
    std::string sunText = std::to_string(sunCount);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, sunText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 760, 30, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    if (isWin) {
        SDL_RenderCopy(renderer, TextureManager::GetTexture("game_completed"), NULL, NULL);
    }
    if (isLose) {
        SDL_RenderCopy(renderer, TextureManager::GetTexture("lose"), NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}
bool Game::running() {
    return isRunning;
}

void Game::clean() {
    for (auto p : plants) delete p;
    for (auto z : zombies) delete z;
    for (auto b : bullets) delete b;
    for (auto s : suns) delete s;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);

    SDL_Quit();
    TTF_Quit();
}


