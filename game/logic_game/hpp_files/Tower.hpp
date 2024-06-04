#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entities.hpp"
#include <list>
#include "Enemy.hpp"
#include <SDL2/SDL.h>

class Tower : public Entities {
public:
    float attackPower;
    float lifeBar;
    int evolveStatus;
    double damage;
    bool selected;
    int shotRate;
    std::list<Enemy*> targetPool;
    SDL_Texture* texture;

    Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate);
    ~Tower() override;

    void upgrade();
    void someVirtualMethod() override;
    void draw(SDL_Renderer* renderer);
    void setPosition(int x, int y);


};

#endif
