#ifndef TIMER_HPP
#define TIMER_HPP

#include "./graphic_game/hpp_files/World.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

// Function to render the timer of the game
// The timer is rendered with the world and the elapsed time
// The timer is rendered with the text, the position and the size

void renderTimer(World& world, Uint32 elapsedTime);

#endif // TIMER_HPP