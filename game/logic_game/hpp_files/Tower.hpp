#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entities.hpp"
#include <list>
#include "Enemy.hpp"

class Tower : public Entities {
public:
    float attackPower;
    float lifeBar;
    int evolveStatus;
    double damage;
    bool selected;
    int shotRate;
    std::list<Enemy*> targetPool;

    Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate);
    ~Tower() override = default;

    void upgrade();
    void someVirtualMethod() override;
};

#endif
