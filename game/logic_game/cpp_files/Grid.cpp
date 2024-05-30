#include "../hpp_files/Grid.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

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
            row.emplace_back(typeCell, 1, 1, false);
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

void Grid::renderGrid(SDL_Renderer* renderer, const std::vector<SDL_Texture*>& textures) {
    const int cellWidth = 20;
    const int cellHeight = 20;
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
    SDL_RenderSetViewport(renderer, nullptr);
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

Cell* Grid::getCellAt(int row, int col) {
    return &cells[row][col];
}

// std::vector<Cell*> Grid::exitCell() {
//     std::vector<Cell*> cellsMarkedOne;
//     for (int i = 0; i < getHeight(); ++i) {
//         for (int j = 0; j < getWidth(); ++j) {
//             if (cells[i][j].typeCell == 1) {
//                 cellsMarkedOne.push_back(&cells[i][j]);
//             }
//         }
//     }
//     return cellsMarkedOne;
// }


