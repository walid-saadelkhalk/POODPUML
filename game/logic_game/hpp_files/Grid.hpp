#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Cell.hpp"
#include "Enemy.hpp"

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
    void renderGrid(SDL_Renderer* renderer, const std::vector<SDL_Texture*>& textures, Enemy& enemy, SDL_Texture* enemyTexture);
};

#endif // GRID_HPP
