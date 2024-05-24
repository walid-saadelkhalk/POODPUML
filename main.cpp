#include "game/graphic_game/hpp_files/World.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/gameLoop.hpp"
#include "game/graphic_game/hpp_files/Button.hpp" 
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

    buttons.push_back(new Button(world.getRenderer(), 1250, 620, 200, 50, "Start", 24));
    buttons.push_back(new Button(world.getRenderer(), 50, 400, 200, 50, "X", 15));
    buttons.push_back(new Button(world.getRenderer(), 50, 250, 400, 150, "Play", 25));
    buttons.push_back(new Button(world.getRenderer(), 50, 400, 400, 150, "Option", 25));
    buttons.push_back(new Button(world.getRenderer(), 50, 550, 400, 150, "Score", 25));

    mainLoop(world, buttons);

    for (Button* button : buttons) {
        delete button;
    }
    world.~World();
    closeGraphic();

    return EXIT_SUCCESS;
}
