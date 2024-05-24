#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

enum class State {
    Intro,
    Menu,
    Settings,
    Game, 
    Score
};

class World {
private:
    State currentState;
    SDL_Window *world;
    SDL_Renderer *renderer;

public:
    World(const char* title, int width, int height);
    ~World();

    void switchState(State newState);
    State getCurrentState();

    SDL_Renderer* getRenderer();  // Méthode publique pour accéder à renderer

    // Déclaration des méthodes ici
    void drawText(const std::string &text, int x, int y, int size);
    SDL_Texture* loadTexture(const std::string &file);
    void renderTexture(SDL_Texture* tex, int x, int y, int w, int h);
    std::vector<SDL_Texture*> loadGifFrames(const std::string &path, int frameCount);
};

#endif
 