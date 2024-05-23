#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/graphic_game/hpp_files/Button.hpp"
#include <iostream>
#include <vector>
#include <vld.h>


//main function to run the game
//initializes the graphics, creates a window, and runs the main game loop


int main(int argc, char *argv[]) {
    if (!initGraphic()) {
        std::cout << "Failed to initialize graphics. Exiting." << std::endl;
        return 1;
    }

    Window window("Intro", 1500, 720);

    if(VLDReportLeaks() == 0)
        std::cout << "No Memory Leaks" << std::endl;
    else
        std::cout << "Memory Leaks" << std::endl;

    std::cout << "la fenetre est fermée" << std::endl;

    window.~Window();
    closeGraphic();

    return EXIT_SUCCESS;
}
