#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <string>

// Class to create a button with a text on it
// The button can be clicked and the text can be displayed
// The button can be created with a renderer, a position, a size, a text and a size of the text

class Button {
    bool clicked;
private:
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Color color;
    std::string text;
    int size;
public:
    Button(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string &text, int size);
    ~Button();
    void draw();
    void click();
    void resetClick();
    bool isClicked() const { return clicked; }
    bool isClickedAtPosition(int x, int y);
};

#endif