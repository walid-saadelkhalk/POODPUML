#include "../hpp_files/InputBox.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

// This class is used to create an input box that can be used to get text input from the user
// The input box will render a rectangle and the text that the user has entered
// The user can enter text by typing on the keyboard


InputBox::InputBox(int x, int y, int w, int h, SDL_Renderer* renderer) 
    : box{x, y, w, h}, textColor{255, 255, 255}, inputText(""), textTexture(nullptr), renderer(renderer) {
    font = TTF_OpenFont("assets/font/MorrisRoman-Black.ttf", 80);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

InputBox::~InputBox() {
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void InputBox::handleEvent(SDL_Event* e) {
    if (e->type == SDL_TEXTINPUT) {
        inputText += e->text.text;
        updateTextTexture();
    } else if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
            inputText.pop_back();
            updateTextTexture();
        }
    }
}

void InputBox::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &box);

    if (textTexture) {
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
        SDL_Rect dstRect = {box.x + 150, box.y + 250, texW, texH};
        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
    }
}

std::string InputBox::getText() const {
    return inputText;
}

void InputBox::updateTextTexture() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
    if (textSurface) {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
    } else {
        std::cerr << "Unable to render text surface: " << TTF_GetError() << std::endl;
    }
}
