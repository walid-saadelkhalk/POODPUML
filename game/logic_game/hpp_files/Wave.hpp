#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include "Observer.hpp" 
#include "Subject.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <algorithm> 

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
