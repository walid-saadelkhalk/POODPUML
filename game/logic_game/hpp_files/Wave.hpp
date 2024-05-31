#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <algorithm> // Ajoutez cette ligne pour std::remove_if

class Wave {
public:
    Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid);
    ~Wave();
    
    // Interdire la copie
    Wave(const Wave&) = delete;
    Wave& operator=(const Wave&) = delete;
    
    // Autoriser le déplacement
    Wave(Wave&&) noexcept = default;
    Wave& operator=(Wave&&) noexcept = default;
    
    void update(Uint32 currentTime);
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const;
    void increaseEnemies(int additionalEnemies);

private:
    int numEnemies;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::vector<Cell>> grid;
    Uint32 lastSpawnTime;
    size_t spawnedEnemies;

    void spawnEnemy();
};

#endif
