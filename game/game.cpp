#include "game.hpp"
#include "./logic_game/hpp_files/data.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "./logic_game/hpp_files/Player.hpp"
#include <iostream>
#include <vector>
#include <utility>

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

    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
}


//player pour le moment à remplacer par enemy quand il sera fait !

void endGame(Player& player, Grid& grid){
    std::pair<int, int> playerPosition = player.getPosition();
    Cell* playerCell = grid.getCellAt(playerPosition.first, playerPosition.second);

    std::cout << "Player position: (" << playerPosition.first << ", " << playerPosition.second << ")" << std::endl;


    if (playerCell->typeCell == 1){
        json(player, 0, 10, 0);
        std::cout << "You win !" << std::endl;
    } else {
        json(player, 0, 0, 10);
        std::cout << "You lose !" << std::endl;
    }
}






