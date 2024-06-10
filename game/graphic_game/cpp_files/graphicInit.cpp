#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


// Method to initialize the graphic library
// This method initializes SDL and SDL_ttf
// Returns true if the initialization was successful, false otherwise


bool initGraphic() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeGraphic() {
    TTF_Quit();
    SDL_Quit();
}
