#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Cell.hpp"
#include "Enemy.hpp"
#include "Wave.hpp"

class Grid {
public:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

    Grid(int width, int height, const std::vector<std::vector<int>>& matrix);
    ~Grid();

    void initializeGrid(const std::vector<std::vector<int>>& matrix);
    static std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename);
    void displayMatrix() const;
    void renderGrid(SDL_Renderer* renderer, const std::vector<SDL_Texture*>& textures, Wave& wave, SDL_Texture* enemyTexture);

    int getWidth() const;
    int getHeight() const;

    Cell* getCellAt(int row, int col);

    // std::vector<Cell*> Grid::exitCell();
};

#endif // GRID_HPP
