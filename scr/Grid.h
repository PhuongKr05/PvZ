#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include "Plant.h"

class Grid {
public:
    static const int ROWS = 6;
    static const int COLS = 7;
    static const int CELL_WIDTH = 80;
    static const int CELL_HEIGHT = 80;

    struct Cell {
        int x = 0;    
        int y = 0;
        bool hasPlant = false;
    } cells[ROWS][COLS];

    Grid();
    bool getCellFromPosition(int mouseX, int mouseY, int& row, int& col);
    void renderGridHighlight(SDL_Renderer* renderer, PlantType selectedPlant);
    void reset();   
};

#endif
