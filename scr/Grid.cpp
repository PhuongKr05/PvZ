#include "Grid.h"

Grid::Grid() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cells[i][j].x = 200 + j * CELL_WIDTH;
            cells[i][j].y = 100 + i * CELL_HEIGHT;
            cells[i][j].hasPlant = false;
        }
    }
}

void Grid::reset() {
    for (int i = 0; i < Grid::ROWS; ++i) {
        for (int j = 0; j < Grid::COLS; ++j) {
            cells[i][j].hasPlant = false;
        }
    }
}
bool Grid::getCellFromPosition(int mouseX, int mouseY, int& row, int& col) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            SDL_Rect cellRect = { cells[i][j].x, cells[i][j].y, CELL_WIDTH, CELL_HEIGHT };
            SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };
            if (SDL_HasIntersection(&cellRect, &mouseRect)) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

void Grid::renderGridHighlight(SDL_Renderer* renderer, PlantType selectedPlant) {
    if (selectedPlant == NONE) return;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int row, col;
    if (getCellFromPosition(mouseX, mouseY, row, col) && !cells[row][col].hasPlant) {
        SDL_Rect highlightRect = { cells[row][col].x, cells[row][col].y, CELL_WIDTH, CELL_HEIGHT };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 50);
        SDL_RenderFillRect(renderer, &highlightRect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
}

