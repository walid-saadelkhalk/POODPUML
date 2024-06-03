#include "../hpp_files/Wave.hpp"
#include <algorithm>
#include <iostream>

Wave::Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid)
    : numEnemies(numEnemies), grid(grid), lastSpawnTime(0), spawnedEnemies(0), enemiesAtExit(0) {
}

Wave::~Wave() {
    // Destructeur, si des ressources dynamiques sont allouées, libérez-les ici
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

    // Supprimer les ennemis qui ont atteint leur objectif et vérifier la défaite
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [this](const std::unique_ptr<Enemy>& enemy) {
            if (enemy->hasReachedGoal()) {
                enemiesAtExit++;
                if (enemiesAtExit >= 3) {
                    gameOver();
                }
                return true;
            }
            return false;
        }), enemies.end());
}


void Wave::spawnEnemy() {
    auto enemy = std::make_unique<Enemy>(0, 0, 100.0f, 50);
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

void Wave::gameOver() {
    std::cout << "Game Over! You lost." << std::endl;
    exit(0);
}
