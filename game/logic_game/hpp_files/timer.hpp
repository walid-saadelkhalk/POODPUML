#ifndef TIMER_HPP
#define TIMER_HPP

#include "./graphic_game/hpp_files/World.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

void renderTimer(World& world, Uint32 elapsedTime);

#endif // TIMER_HPP