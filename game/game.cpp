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

// This file contains the different functions used in the game
// The functions are used to load the matrix, render the matrix, end the game and reset the game
// The functions are used to load the matrix from a file, render the matrix with the player, the grid and the wave
// The file is used to play the controller role between the graphic and the logic part of the game

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
    for (int i = 0; i <= 21; ++i) {
        std::string path = "assets/images/" + std::to_string(i) + ".png";
        SDL_Texture* texture = world.loadTexture(path);
        if (texture) {
            textures.push_back(texture);
        }
    }

    std::vector<SDL_Texture*> enemyTextures;
    for (int i = 0; i <= 5; ++i) {
        std::string path = "assets/images/Mordor/enemy/" + std::to_string(i) + ".png";
        SDL_Texture* texture = world.loadTexture(path);
        if (texture) {
            enemyTextures.push_back(texture);
        }
    }

    SDL_Texture* towerTexture = world.loadTexture("assets/images/Mordor/Tower.png");
    if (!towerTexture) {
        std::cerr << "Erreur lors du chargement de l'image de la tour" << std::endl;
    }

    grid.renderGrid(world.getRenderer(), textures, wave, player, enemyTextures, towerTexture);

    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
    for (SDL_Texture* texture : enemyTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(towerTexture);
}



void endGame(Player& player, const Grid& grid, int gameTime, bool won, int nb_wave) {
    json(player, 0, nb_wave, gameTime);
    if (won) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "Game Over! You lost." << std::endl;
    }
    std::cout << "Game time: " << gameTime << " seconds" << std::endl;
}

void resetGame(World& world, std::unique_ptr<Player>& player, Grid& grid, Wave& wave) {
    std::cout << "Resetting game..." << std::endl; 

    std::string playerName = player->getName();

    player->clearTowers();  
    std::vector<std::vector<int>> matrix = loadMatrix(world);
    grid.reset(matrix);

    player = std::make_unique<Player>(playerName, 12, 5, 3, grid.cells, world.getRenderer());
    wave.reset(10, grid.cells);

    std::cout << "Game reset complete." << std::endl;
}







