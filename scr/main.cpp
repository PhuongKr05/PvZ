#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.init("Plants vs Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, false);

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(16); 
    }

    game.clean();
    return 0;
}
