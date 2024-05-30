#include "game/graphic_game/hpp_files/World.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/gameLoop.hpp"
#include "game/graphic_game/hpp_files/Button.hpp" 
#include "./logic_game/hpp_files/player.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "game/game.hpp"

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// The main function of the game that initializes the graphics and creates the window
// It also creates the buttons and the main loop of the game
// The main loop will handle the events and render the game

int main(int argc, char *argv[]) {
    if (!initGraphic()) {
        std::cout << "Échec de l'initialisation des graphiques. Sortie." << std::endl;
        return 1;
    }


    World world("Intro", 1500, 720);
    std::vector<Button*> buttons;
    Player player("Sam Gamgeez");
    std::vector<std::vector<int>> matrix = loadMatrix(world);
    Grid grid(matrix[0].size(), matrix.size(), matrix);


    buttons.push_back(new Button(world.getRenderer(), 1250, 620, 200, 50, "Start", 24));
    buttons.push_back(new Button(world.getRenderer(), 1400, 10, 50, 50, "X", 25));
    buttons.push_back(new Button(world.getRenderer(), 50, 250, 400, 150, "Play", 25));
    buttons.push_back(new Button(world.getRenderer(), 50, 400, 400, 150, "Option", 25));
    buttons.push_back(new Button(world.getRenderer(), 50, 550, 400, 150, "Score", 25));
    buttons.push_back(new Button(world.getRenderer(), 200, 250, 400, 150, "THE SHIRE", 40));
    buttons.push_back(new Button(world.getRenderer(), 900, 250, 400, 150, "MORDOR", 40));
    buttons.push_back(new Button(world.getRenderer(), 350, 500, 100, 100, "ON", 20));
    buttons.push_back(new Button(world.getRenderer(), 1050, 500, 100, 100, "OFF", 20));
    buttons.push_back(new Button(world.getRenderer(), 400, 10, 50, 50, "X", 25));
    
    mainLoop(world, buttons, player, grid);

    for (Button* button : buttons) {
        delete button;
    }
    world.~World();
    closeGraphic();

    return EXIT_SUCCESS;
}
