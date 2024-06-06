#include "../hpp_files/Tower.hpp"
#include "../hpp_files/Observer.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>


Tower::Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate, int range)
    : Entities(x, y), attackPower(attackPower), lifeBar(lifeBar), evolveStatus(evolveStatus), damage(damage), selected(selected), shotRate(shotRate), range(range) {

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

    // Draw the detection zone
    int radius = range * 200;
    int x = posX * 200 + 20;
    int y = posY * 200 + 20;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
    SDL_RenderPresent(renderer);
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


void Tower::update(Wave& wave) {
    std::cout << "on a vu quelque chose" << std::endl;
    for (auto& enemy : wave.getEnemies()) {
        // Check if enemy is within range of tower
        int dx = enemy->posX - posX;
        int dy = enemy->posY - posY;
        int distanceSquared = dx * dx + dy * dy;
        if (distanceSquared <= range * range) {
            // Enemy is in range, so attack enemy
            std::cout << "Tower attacked enemy at position (" << enemy->posX << ", " << enemy->posY << ")" << std::endl;
            attack(*enemy);
        }
    }
}

void Tower::attack(Enemy& enemy) {
    enemy.lifeBar -= attackPower;
    std::cout << enemy.lifeBar << std::endl;
    // std::cout << "Tower attacked enemy  (" << enemy.posX << ", " << enemy.posY << ")" << std::endl;
}
