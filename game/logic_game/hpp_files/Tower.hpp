#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entities.hpp"
#include "Observer.hpp"
#include <list>
#include "Enemy.hpp"
#include "Wave.hpp"
#include <SDL2/SDL.h>

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
    

};

#endif
