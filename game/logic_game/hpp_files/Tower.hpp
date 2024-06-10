#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entities.hpp"
#include "Observer.hpp"
#include <list>
#include "Enemy.hpp"
#include "Wave.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

// This class represents a tower 
// The tower can be created with a position, an attack power, a life bar, an evolve status, a damage, a selected state, a shot rate and a range
// The tower can be displayed with the position
// The tower can upgrade, attack an enemy, draw, set a position and update

class Tower : public Entities, public Observer {
public:
    float attackPower;
    float lifeBar;
    int evolveStatus;
    double damage;
    bool selected;
    int shotRate;
    int range;
    SDL_Texture* texture;

    Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate, int range);
    ~Tower() override;

    void upgrade();
    void someVirtualMethod() override;
    void draw(SDL_Renderer* renderer);
    void setPosition(int x, int y);
    void update(Wave& wave) override;
    void attack(Enemy& enemy);
    void shoot(Enemy* target);
    void renderLaser(SDL_Renderer* renderer);

private:
    Uint32 lastShotTime;
    Enemy* currentTarget;
    
};

#endif
