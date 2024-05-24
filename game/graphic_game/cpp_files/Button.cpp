#include "../hpp_files/Button.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;


Button::Button(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string &text, int size) : clicked(false){
    this->renderer = renderer;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    this->text = text;
    this->size = size;
    bool clicked;

    TTF_Font *font = TTF_OpenFont("assets/font/MorrisRoman-Black.TTF", size);
    if (font == nullptr) {
        std::cout << "Erreur lors de l'ouverture de la police : " << TTF_GetError() << std::endl;
        exit(1);
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 199, 118});
    if (surface == nullptr) {
        std::cout << "Erreur lors de la création de la surface : " << TTF_GetError() << std::endl;
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cout << "Erreur lors de la création de la texture : " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::draw() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    // if (clicked) {
    //     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // } else {
    //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // }

    // SDL_RenderDrawRect(renderer, &rect);
}

void Button::click() {
    this->clicked = true;
}

void Button::resetClick() {
    this->clicked = false;
}

bool Button::isClickedAtPosition(int x, int y) {
    cout << "Button rect: x=" << rect.x << ", y=" << rect.y << ", w=" << rect.w << ", h=" << rect.h << endl;
    cout << "Mouse click: x=" << x << ", y=" << y << endl;

    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

// void Button::highlight() {

//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 

//     SDL_RenderDrawRect(renderer, &rect);
// }
