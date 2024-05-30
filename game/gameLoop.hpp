#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "graphic_game/hpp_files/World.hpp"
#include "graphic_game/hpp_files/Button.hpp"
#include "./logic_game/hpp_files/Player.hpp"
#include "./logic_game/hpp_files/Grid.hpp"

#include <vector>

// The main loop of the game
// It will handle the events and render the game based on the current state 
// The main loop will call different functions to render the different pages of the game

void mainLoop(World& world, std::vector<Button*>& buttons, Player& player, Grid& grid, Enemy& enemy);


#endif
