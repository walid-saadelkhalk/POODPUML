#include "../hpp_files/Wave.hpp"
#include "../hpp_files/Subject.hpp"
#include "../hpp_files/Observer.hpp"
#include <algorithm> 
#include <iostream>
#include <stdio.h>

Wave::Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid)
    : numEnemies(numEnemies), grid(grid), lastSpawnTime(0), spawnedEnemies(0) {
}

Wave::~Wave() {
    // Destructeur, si des ressources dynamiques sont allouées, libérez-les ici
}

void Wave::attach(Observer* observer){
    towers.push_back(observer);
}

void Wave::detach(Observer* observer){
    towers.erase(std::remove(towers.begin(), towers.end(), observer), towers.end());
}

void Wave::notify(){
    std::cout << "Enemy notify" << std::endl;
    for (Observer* tower : towers) {

        tower->update(*this);
    }
}

void Wave::update(Uint32 currentTime) {
    if (spawnedEnemies < numEnemies && currentTime - lastSpawnTime >= 300) {
        spawnEnemy();
        lastSpawnTime = currentTime;
    }

    // Mettre à jour et vérifier les ennemis
    for (auto& enemy : enemies) {
        enemy->move();
    }

    // Supprimer les ennemis qui ont atteint leur objectif
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [this](const std::unique_ptr<Enemy>& enemy) {
            bool shouldRemove = enemy->hasReachedGoal() || enemy->getLifeBar() <= 0;
            if (shouldRemove && enemy->getLifeBar() <= 0) {
                ++deadEnemies; 
            }
            return shouldRemove;
        }), enemies.end());
}

void Wave::spawnEnemy() {
    auto enemy = std::make_unique<Enemy>(0, 0, 90.0f, 50);
    enemy->setPath(grid);
    enemies.push_back(std::move(enemy));
    spawnedEnemies++;
}

const std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() const {
    return enemies;
}

void Wave::increaseEnemies(int additionalEnemies) {
    numEnemies += additionalEnemies;
}
