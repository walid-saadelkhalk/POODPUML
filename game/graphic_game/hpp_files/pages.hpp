#ifndef PAGES_HPP
#define PAGES_HPP

#include "World.hpp"
#include "Button.hpp"
#include "./logic_game/hpp_files/timer.hpp"
#include "./logic_game/hpp_files/Player.hpp"

//This file contains the different pages of the game
//The intro page, the menu page, the settings page, the score page and the game page
//Each page is displayed with the world, the buttons and the player
//The pages are displayed with the different buttons and the different textures

void cleanUpTextures(std::vector<SDL_Texture*>& textures);
void cleanUpButtons(std::vector<SDL_Texture*>& textures);
void introPage(World& world, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame);
void menuPage(World& world, std::vector<Button*>& buttons);
void settingsPage(World& world, std::vector<Button*>& buttons);
void scorePage(World& world, std::vector<Button*>& buttons,std::unique_ptr<Player>& player);
void gamePage(World& world, std::vector<Button*>& buttons, int waveNumber,std::unique_ptr<Player>& player, Player& players);

#endif