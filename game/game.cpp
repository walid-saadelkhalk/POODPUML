#include "game.hpp"
#include "./logic_game/hpp_files/data.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "./logic_game/hpp_files/Player.hpp"
#include <iostream>
#include <vector>

std::vector<std::vector<int>> loadMatrix(World& world){

    // Load the matrix from the file
    std::vector<std::vector<int>> matrix = Grid::readMatrixFromFile("matrice.txt");
    if (matrix.empty()) {
        std::cerr << "Erreur: Impossible de lire la matrice depuis le fichier." << std::endl;
        return std::vector<std::vector<int>>();
    }

    //End of loading textures
    return matrix;
}

void renderMatrix(World& world, Grid& grid) {
    std::vector<SDL_Texture*> textures;
    for (int i = 0; i <= 6; ++i) {
        std::string path = "assets/images/" + std::to_string(i) + ".png";
        SDL_Texture* texture = world.loadTexture(path);
        if (texture) {
            textures.push_back(texture);
        }
    }
    grid.renderGrid(world.getRenderer(), textures);
}






