#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class InputBox {
public:
    InputBox(int x, int y, int w, int h, SDL_Renderer* renderer);
    ~InputBox();
    void handleEvent(SDL_Event* e);
    void render();
    std::string getText() const;

private:
    SDL_Rect box;
    SDL_Color textColor;
    std::string inputText;
    SDL_Texture* textTexture;
    TTF_Font* font;
    SDL_Renderer* renderer;

    void updateTextTexture();
};
