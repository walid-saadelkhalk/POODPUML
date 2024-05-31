#include "../hpp_files/Wave.hpp"

Wave::Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid)
    : numEnemies(numEnemies), grid(grid), lastSpawnTime(0), spawnedEnemies(0) {
}

void Wave::update(Uint32 currentTime) {
    if (spawnedEnemies < numEnemies && currentTime - lastSpawnTime >= 300) {
        spawnEnemy();
        lastSpawnTime = currentTime;
    }

    for (auto& enemy : enemies) {
        enemy->move();
    }
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
