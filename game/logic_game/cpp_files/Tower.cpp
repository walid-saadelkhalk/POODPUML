#include "../hpp_files/Tower.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

Tower::Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate)
    : Entities(x, y), attackPower(attackPower), lifeBar(lifeBar), evolveStatus(evolveStatus), damage(damage), selected(selected), shotRate(shotRate) {

}

Tower::~Tower() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Tower::upgrade() {
    // Implémentez la logique pour améliorer la tour ici
}

void Tower::someVirtualMethod() {
    // Implémentez la méthode virtuelle ici
}

void Tower::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = { posX * 200, posY * 200, 40, 40 };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Tower::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

    // texture = IMG_LoadTexture(renderer, "assets/images/Mordor/Tower.jpg");
    // if (!texture) {
    //     std::cerr << "Failed to load tower texture: " << IMG_GetError() << std::endl;
    // } else {
    //     std::cout << "Tower texture loaded successfully!" << std::endl;
    // }