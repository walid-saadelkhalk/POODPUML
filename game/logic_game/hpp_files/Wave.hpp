#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>

class Wave {
public:
    Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid);
    ~Wave();
    void update(Uint32 currentTime);
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const; 


private:
    int numEnemies;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::vector<Cell>> grid;
    Uint32 lastSpawnTime;
    size_t spawnedEnemies;

    void spawnEnemy();
};

#endif 
