#include "../hpp_files/World.hpp"
#include <SDL2/SDL_ttf.h>
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

void World::drawText(const std::string &text, int x, int y, int size) {
    TTF_Font* font = TTF_OpenFont("assets/font/MorrisRoman-Black.ttf", size);

    if (font == nullptr) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255}; 

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == nullptr) {
        std::cerr << "Erreur lors de la création de la surface de texte : " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (textTexture == nullptr) {
        std::cerr << "Erreur lors de la création de la texture de texte : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* World::loadTexture(const std::string &file) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, file.c_str());
    if (newTexture == nullptr) {
        std::cerr << "Erreur lors du chargement de l'image " << file << " : " << IMG_GetError() << std::endl;
    } else {
        std::cout << "Image chargée avec succès : " << file << std::endl;
    }
    return newTexture;
}

void World::renderTexture(SDL_Texture* tex, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}

std::vector<SDL_Texture*> World::loadGifFrames(const std::string &path, int frameCount) {
    std::vector<SDL_Texture*> frames;
    for (int i = 0; i < frameCount; ++i) {
        std::string framePath = path + "/intro_" + (i < 10 ? "00" : (i < 100 ? "0" : "")) + std::to_string(i) + ".png";
        SDL_Texture* frame = loadTexture(framePath);
        if (frame != nullptr) {
            frames.push_back(frame);
        } else {
            std::cerr << "Erreur lors du chargement de la frame : " << framePath << std::endl;
        }
    }
    return frames;
}
