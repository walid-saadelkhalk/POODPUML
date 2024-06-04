#ifndef GAME_HPP
#define GAME_HPP 

#include "graphic_game/hpp_files/World.hpp"
#include "logic_game/hpp_files/Grid.hpp"
#include "logic_game/hpp_files/Player.hpp"
#include "logic_game/hpp_files/Wave.hpp"


std::vector<std::vector<int>> loadMatrix(World& world);

void renderMatrix(World& world, Grid& grid, Wave& wa, Player& player);



void endGame(Player& player, Grid& grid, int time);


#endif // GAME.HPP