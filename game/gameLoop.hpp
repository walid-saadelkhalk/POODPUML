#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "graphic_game/hpp_files/Window.hpp"
#include "graphic_game/hpp_files/Button.hpp"
#include <vector>

// The main loop of the game
// It will handle the events and render the game based on the current state 
// The main loop will call different functions to render the different pages of the game

void mainLoop(Window& window, std::vector<Button*>& buttons);
void introPage(Window& window, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame);
void menuPage(Window& window, std::vector<Button*>& buttons, bool& levelSelected);

#endif
