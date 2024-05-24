#include "../hpp_files/World.hpp"
#include <iostream>

World::World(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur lors de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
        exit(1);
    }

    world = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (world == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(world, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        exit(1);
    }

    currentState = State::Intro; 
}

World::~World() {
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(world);
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer* World::getRenderer() {
    return renderer;
}

void World::switchState(State newState) {
    switch(newState) {
        case State::Intro:
            SDL_SetWindowTitle(world, "Intro");
            break;
        case State::Menu: 
            SDL_SetWindowTitle(world, "Menu");
            break;
        case State::Settings: 
            SDL_SetWindowTitle(world, "Settings");
            break;
        case State::Game: 
            SDL_SetWindowTitle(world, "Game");
            break;
        case State::Score:
            SDL_SetWindowTitle(world, "Score");
            break;
        default:
            std::cerr << "État invalide !" << std::endl;
            break;
    }
    currentState = newState;
}

State World::getCurrentState() {
    return currentState;
}


