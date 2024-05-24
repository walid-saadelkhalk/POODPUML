#ifndef PAGES_HPP
#define PAGES_HPP

#include "World.hpp"
#include "Button.hpp"

void introPage(World& world, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame);
void menuPage(World& world, std::vector<Button*>& buttons, bool& levelSelected);

#endif