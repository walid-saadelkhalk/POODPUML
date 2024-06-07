#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include "Observer.hpp" 
#include "Subject.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <algorithm> 

// This class represents a wave of enemies
// The wave can be created with a number of enemies and a grid
// The wave can be displayed with the number of enemies, the grid, the last spawn time, the number of spawned enemies and the number of enemies at the exit
// The wave can be rendered with a current time and the number of enemies at the exit

class Wave : public Subject{
public:
    Wave(int numEnemies, const std::vector<std::vector<Cell>>& grid);
    ~Wave();
    
    Wave(const Wave&) = delete;
    Wave& operator=(const Wave&) = delete;
    
    Wave(Wave&&) noexcept = default;
    Wave& operator=(Wave&&) noexcept = default;
    
    bool update(Uint32 currentTime, int& enemiesAtExit);
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const;
    void increaseEnemies(int additionalEnemies);
    int getEnemiesAtExit() const ;

    void reset(int numEnemies, const std::vector<std::vector<Cell>>& grid);


    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();


private:
    std::vector<Observer*> towers;
    int numEnemies;
    int deadEnemies;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::vector<Cell>> grid;
    Uint32 lastSpawnTime;
    size_t spawnedEnemies;
    int enemiesAtExit;

    void spawnEnemy();

    void gameOver(); 

};

#endif
