#ifndef GAME_HPP
#define GAME_HPP 

#include "graphic_game/hpp_files/World.hpp"
#include "logic_game/hpp_files/Grid.hpp"
#include "logic_game/hpp_files/Player.hpp"
#include "logic_game/hpp_files/Wave.hpp"

// This file contains the different functions used in the game
// The functions are used to load the matrix, render the matrix, end the game and reset the game
// The functions are used to load the matrix from a file, render the matrix with the player, the grid and the wave
// The file is used to play the controller role between the graphic and the logic part of the game

std::vector<std::vector<int>> loadMatrix(World& world);

void renderMatrix(World& world, Grid& grid, Wave& wa, Player& player);

void endGame(Player& player, const Grid& grid, int gameTime, bool won, int nb_wave);

void resetGame(World& world, std::unique_ptr<Player>& player, Grid& grid, Wave& wave);

#endif // GAME.HPP