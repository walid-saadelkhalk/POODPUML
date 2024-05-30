#ifndef GAME_HPP
#define GAME_HPP 

#include "graphic_game/hpp_files/World.hpp"
#include "logic_game/hpp_files/Grid.hpp"

std::vector<std::vector<int>> loadMatrix(World& world);

void renderMatrix(World& world, Grid& grid, Enemy& enemy);


#endif // GAME.HPP