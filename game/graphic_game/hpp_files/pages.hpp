#ifndef PAGES_HPP
#define PAGES_HPP

#include "World.hpp"
#include "Button.hpp"

void cleanUpTextures(std::vector<SDL_Texture*>& textures);
void cleanUpButtons(std::vector<SDL_Texture*>& textures);
void introPage(World& world, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame);
void menuPage(World& world, std::vector<Button*>& buttons);
void settingsPage(World& world, std::vector<Button*>& buttons);
void scorePage(World& world, std::vector<Button*>& buttons);

#endif