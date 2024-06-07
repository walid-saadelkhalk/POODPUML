#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// This class is used to create an input box that can be used to get text input from the user
// The input box will render a rectangle and the text that the user has entered
// The user can enter text by typing on the keyboard

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
