#include "game/graphic_game/hpp_files/World.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/graphic_game/hpp_files/Sound.hpp"
#include "game/gameLoop.hpp"
#include "game/graphic_game/hpp_files/Button.hpp" 
#include "./logic_game/hpp_files/Player.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include "./logic_game/hpp_files/Enemy.hpp"
#include "game/game.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <string>

std::string menuBackgroundPath = "assets/images/menu_page.png";

int main(int argc, char *argv[]) {
    if (!initGraphic()) {
        std::cout << "Échec de l'initialisation des graphiques. Sortie." << std::endl;
        return 1;
    }
    Sound::getInstance().playMusic("assets/song/gameSong.mp3");
    World world("Intro", 1500, 720);
    std::vector<Button*> buttons;
    std::vector<std::vector<int>> matrix = loadMatrix(world);
    Grid grid(matrix[0].size(), matrix.size(), matrix);
    std::unique_ptr<Player> player = std::make_unique<Player>("Sam Gamgeez", 12, 5, 3, grid.cells, world.getRenderer());

    

    // Initialiser l'ennemi à la position de départ
    Enemy enemy(0, 7, 100.0f, 20); // Initialiser avec les coordonnées de départ (0, 7)
    // enemy.setPath(grid.cells);

    buttons.push_back(new Button(world.getRenderer(), 1250, 620, 200, 50, "Start", 24));
    buttons.push_back(new Button(world.getRenderer(), 1410, 10, 50, 50, "X", 25));
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

    // player.~Player();
    world.~World();
    grid.~Grid();
    enemy.~Enemy();
    // sound.~Sound();
    closeGraphic();

    Sound::getInstance().stopMusic();

    return EXIT_SUCCESS;
}
