#include "../hpp_files/Wave.hpp"
#include "../hpp_files/Subject.hpp"
#include "../hpp_files/Observer.hpp"
#include <algorithm> 
#include <iostream>
#include <stdio.h>

// This file is a class that creates a wave
// The wave can be created with a number of enemies and a grid
// The wave can be displayed with the number of enemies, the grid, the last spawn time, the number of spawned enemies and the number of enemies at the exit
// The wave can be rendered with a current time and the number of enemies at the exit

Wave::Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid)
    : numEnemies(numEnemies), grid(grid), lastSpawnTime(0), spawnedEnemies(0), enemiesAtExit(0) {
}

Wave::~Wave() {
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


bool Wave::update(Uint32 currentTime, int& enemiesAtExit) {
    if (spawnedEnemies < numEnemies && currentTime - lastSpawnTime >= 300) {
        spawnEnemy();
        lastSpawnTime = currentTime;
    }

    for (auto& enemy : enemies) {
        enemy->move();
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [this, &enemiesAtExit](const std::unique_ptr<Enemy>& enemy) {
            bool shouldRemove = enemy->hasReachedGoal() || enemy->getLifeBar() <= 0;
            if (enemy->hasReachedGoal()) {
                enemiesAtExit++;
                return true;
            }
            if (shouldRemove && enemy->getLifeBar() <= 0) {
                ++deadEnemies; 
            }
            return shouldRemove;
        }), enemies.end());

    if (enemiesAtExit >= 3) {
        return true;
    }

    return false;
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

void Wave::gameOver() {
    std::cout << "Game Over! You lost." << std::endl;
}

int Wave::getEnemiesAtExit() const {
    return enemiesAtExit;
}

void Wave::reset(int numEnemies, const std::vector<std::vector<Cell>>& grid) {
    this->numEnemies = numEnemies;
    this->grid = grid;
    this->lastSpawnTime = 0;
    this->spawnedEnemies = 0;
    this->enemiesAtExit = 0;
    this->enemies.clear();
}
