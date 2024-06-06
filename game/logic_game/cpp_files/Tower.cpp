#include "../hpp_files/Tower.hpp"
#include "../hpp_files/Observer.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <ctime> 



Tower::Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate, int range)
    : Entities(x, y), attackPower(attackPower), lifeBar(lifeBar), evolveStatus(evolveStatus), damage(damage), selected(selected), shotRate(shotRate), range(range), lastShotTime(0), currentTarget(nullptr) {

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


void Tower::update(Wave& wave) {
    currentTarget = nullptr;
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastShotTime >= shotRate) {
        for (const auto& enemy : wave.getEnemies()) {
            int dx = enemy->posX - posX;
            int dy = enemy->posY - posY;
            int distanceSquared = dx * dx + dy * dy;
            if (distanceSquared <= range * range) {
                currentTarget = enemy.get();
                shoot(currentTarget);
                // std::cout << "Tower attacked enemy  (" << currentTarget->posX << ", " << currentTarget->posY << ")" << std::endl;
                lastShotTime = currentTime;
                break; // Une tour tire sur un seul ennemi à la fois
            }
        }
    }
}

void Tower::attack(Enemy& enemy) {
    enemy.lifeBar -= attackPower;
    std::cout << enemy.lifeBar << std::endl;
    // std::cout << "Tower attacked enemy  (" << enemy.posX << ", " << enemy.posY << ")" << std::endl;
}


void Tower::shoot(Enemy* target) {
    currentTarget = target;
    attack(*currentTarget);
    // Logic to create and manage projectiles can be added here if necessary
}

 

void Tower::renderLaser(SDL_Renderer* renderer) {
    if (currentTarget && currentTarget->lifeBar > 0) {
        int towerCenterX = posX * 40 + 20;
        int towerCenterY = posY * 40 + 20;
        int enemyCenterX = currentTarget->posX * 40 + 20;
        int enemyCenterY = currentTarget->posY * 40 + 20;

        std::cout << "Drawing laser from (" << towerCenterX << ", " << towerCenterY << ") to ("
                  << enemyCenterX << ", " << enemyCenterY << ")" << std::endl;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

        // Initialiser le générateur de nombres aléatoires
        srand(time(nullptr));

        // Calculer la direction du laser
        float dx = enemyCenterX - towerCenterX;
        float dy = enemyCenterY - towerCenterY;
        float distance = sqrt(dx * dx + dy * dy);
        float stepX = dx / distance;
        float stepY = dy / distance;

        // Dessiner chaque segment du laser avec plusieurs points
        int pointSize = 10; // Ajustez la taille du point selon vos préférences
        float stepSize = 6; // Ajustez la taille de l'intervalle entre les points selon vos préférences
        float randomness = 3.0f; // Ajustez l'amplitude de la variation aléatoire
        float speedFactor = 1.0f; // Ajustez le facteur de vitesse pour rendre le laser plus rapide

        for (float i = 0; i < distance; i += stepSize * speedFactor) {
            int startX = towerCenterX + stepX * i;
            int startY = towerCenterY + stepY * i;
            int endX = towerCenterX + stepX * (i + stepSize * speedFactor);
            int endY = towerCenterY + stepY * (i + stepSize * speedFactor);

            // Dessiner plusieurs points le long du segment avec une variation aléatoire
            for (int j = 0; j < pointSize; ++j) {
                int x = startX + (endX - startX) * j / pointSize + (rand() % (int)(2 * randomness) - randomness);
                int y = startY + (endY - startY) * j / pointSize + (rand() % (int)(2 * randomness) - randomness);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}











// void Tower::update() {
//     // Implémentation de la méthode de l'interface Observer
//     // Appelée lorsque la vague notifie les observateurs
//     Wave& wave = getWave(); // Méthode pour obtenir la vague actuelle
//     update(wave);
// }

