#include "game/graphic_game/hpp_files/World.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/gameLoop.hpp"
#include "game/graphic_game/hpp_files/Button.hpp" 
#include "./logic_game/hpp_files/player.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "./logic_game/hpp_files/Enemy.hpp"
#include "game/game.hpp"

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (!initGraphic()) {
        std::cout << "Échec de l'initialisation des graphiques. Sortie." << std::endl;
        return 1;
    }

    World world("Intro", 1500, 720);
    std::vector<Button*> buttons;
    Player player("Sam Gamgeez", 12, 5);
    std::vector<std::vector<int>> matrix = loadMatrix(world);
    Grid grid(matrix[0].size(), matrix.size(), matrix);

    Enemy enemy(0, 140, 100.0f, 20); 
    enemy.setPath(grid.cells);

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
    buttons.push_back(new Button(world.getRenderer(), 350, 100, 50, 50, "LOSE", 25));
    buttons.push_back(new Button(world.getRenderer(), 1350, 100, 50, 50, "LOSE2", 25));
    
    mainLoop(world, buttons, player, grid, enemy);

    for (Button* button : buttons) {
        delete button;
    }

    player.~Player();
    world.~World();
    grid.~Grid();
    closeGraphic();

    return EXIT_SUCCESS;
}
