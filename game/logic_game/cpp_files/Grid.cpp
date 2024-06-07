#include "../hpp_files/Grid.hpp"
#include "../hpp_files/PLayer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL_image.h>

// This file is a class that creates a grid
// The grid can be created with a width, a height and a matrix
// The grid can be displayed with the matrix
// The grid can be rendered with a renderer, textures, a wave, a player, an enemy texture and a tower texture

Grid::Grid(int width, int height, const std::vector<std::vector<int>>& matrix)
    : width(width), height(height) {
    initializeGrid(matrix);
}

Grid::~Grid() {}

void Grid::initializeGrid(const std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < height; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < width; ++j) {
            int typeCell = matrix[i][j];
            row.emplace_back(typeCell, i, j, false);
        }
        cells.push_back(row);
    }
}

std::vector<std::vector<int>> Grid::readMatrixFromFile(const std::string& filename) {
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier: " << filename << std::endl;
        return matrix;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        char ch;
        while (ss >> ch) {
            if (isdigit(ch)) {
                row.push_back(ch - '0');
            }
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }

    if (matrix.empty()) {
        std::cerr << "Erreur: La matrice lue à partir du fichier est vide." << std::endl;
    } else {
        std::cout << "Matrice lue avec succès." << std::endl;
    }

    return matrix;
}

void Grid::displayMatrix() const {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            std::cout << cell.typeCell << ' ';
        }
        std::cout << std::endl;
    }
}

void Grid::renderGrid(SDL_Renderer* renderer, const std::vector<SDL_Texture*>& textures, Wave& wave, Player& player,SDL_Texture* enemyTexture, SDL_Texture* towerTexture) {
    const int cellWidth = 40;
    const int cellHeight = 40;
    const int maxWidth = 1000;
    const int maxHeight = 720;
    const int maxColumns = maxWidth / cellWidth;
    const int maxRows = maxHeight / cellHeight;

    SDL_Rect gridViewport;
    gridViewport.x = 0;
    gridViewport.y = 0;
    gridViewport.w = maxWidth;
    gridViewport.h = maxHeight;
    SDL_RenderSetViewport(renderer, &gridViewport);

    for (int i = 0; i < height && i < maxRows; ++i) {
        for (int j = 0; j < width && j < maxColumns; ++j) {
            int typeCell = cells[i][j].typeCell;
            if (typeCell >= 1 && typeCell <= textures.size()) {
                SDL_Rect dstRect = { j * cellWidth, i * cellHeight, cellWidth, cellHeight };
                SDL_RenderCopy(renderer, textures[typeCell - 1], nullptr, &dstRect);
            }
        }
    }
    
    // Render all enemies in the wave
    for (const auto& enemy : wave.getEnemies()) {
        SDL_Rect enemyRect = { enemy->posX * cellWidth, enemy->posY * cellHeight, cellWidth, cellHeight };
        SDL_RenderCopy(renderer, enemyTexture, nullptr, &enemyRect);
    }

    // Render all towers
    for (const auto& tower : player.getTowers()) {
        SDL_Rect towerRect = { tower->posX * cellWidth, tower->posY * cellHeight, cellWidth, cellHeight };
        SDL_RenderCopy(renderer, towerTexture, nullptr, &towerRect);
    }

    SDL_RenderSetViewport(renderer, nullptr);
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

bool Grid::isCellEmpty(int x, int y) {
    if (cells[y][x].typeCell == 1) {
        std::cout << "Cellule non occupée" << std::endl;
    return cells[y][x].occupied == false;
    }
    return false;
}

bool Grid::setCellTexture(int x, int y, SDL_Texture* towerTexture) {
    if (cells[y][x].occupied == false) {
        cells[y][x].occupied = true;
        return true;
    }
    SDL_Texture *texture = towerTexture;
    if (texture == nullptr) {
        std::cerr << "Erreur lors de la lecture de la texture." << std::endl;
        return false;
    }
    return false;
}

Cell* Grid::getCellAt(int row, int col) {
    return &cells[row][col];
}

void Grid::reset(const std::vector<std::vector<int>>& matrix) {
    std::cout << "Resetting grid..." << std::endl;
    this->width = matrix[0].size();
    this->height = matrix.size();
    this->cells.clear();
    initializeGrid(matrix);
    std::cout << "Grid reset complete." << std::endl;
}

