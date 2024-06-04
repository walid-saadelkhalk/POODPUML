#include "game.hpp"
#include "./logic_game/hpp_files/data.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "./logic_game/hpp_files/Player.hpp"
#include "./logic_game/hpp_files/Enemy.hpp"
#include "./logic_game/hpp_files/Wave.hpp"
#include "./logic_game/hpp_files/Tower.hpp"
#include <iostream>
#include <vector>
#include <utility>

std::vector<std::vector<int>> loadMatrix(World& world) {
    // Load the matrix from the file
    std::vector<std::vector<int>> matrix = Grid::readMatrixFromFile("matrice.txt");
    if (matrix.empty()) {
        std::cerr << "Erreur: Impossible de lire la matrice depuis le fichier." << std::endl;
        return std::vector<std::vector<int>>();
    }

    //End of loading textures
    return matrix;
}

void renderMatrix(World& world, Grid& grid, Wave& wave, Player& player) {
    std::vector<SDL_Texture*> textures;
    for (int i = 0; i <= 6; ++i) {
        std::string path = "assets/images/" + std::to_string(i) + ".png";
        SDL_Texture* texture = world.loadTexture(path);
        if (texture) {
            textures.push_back(texture);
        }
    }

    SDL_Texture* enemyTexture = world.loadTexture("assets/images/Mordor/Boromir.jpg");
    if (!enemyTexture) {
        std::cerr << "Erreur lors du chargement de l'image de l'ennemi" << std::endl;
    }

    SDL_Texture* towerTexture = world.loadTexture("assets/images/Mordor/Tower.jpg");
    if (!towerTexture) {
        std::cerr << "Erreur lors du chargement de l'image de la tour" << std::endl;
    }

    grid.renderGrid(world.getRenderer(), textures, wave, player,enemyTexture, towerTexture);

    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(towerTexture);
}


void endGame(Player& player, Grid& grid, int gameTime) {
    std::pair<int, int> playerPosition = player.getPosition();
    Cell* playerCell = grid.getCellAt(playerPosition.first, playerPosition.second);

    std::cout << "Player position: (" << playerPosition.first << ", " << playerPosition.second << ")" << std::endl;

    if (playerCell->typeCell == 1) {
        json(player, 0, 10, gameTime);
        std::cout << "You win !" << std::endl;
    } else {
        json(player, 0, 0, gameTime);
        std::cout << "You lose !" << std::endl;
    }

    std::cout << "Game time: " << gameTime << " seconds" << std::endl;
}
