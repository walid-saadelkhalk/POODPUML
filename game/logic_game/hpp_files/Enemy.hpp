#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entities.hpp"
#include <vector>
#include "Cell.hpp"

class Enemy : public Entities{
public:
    float lifeBar;
    int height;
    std::vector<Cell*> path;
    size_t currentStep;

    Enemy(int x, int y, float lifeBar, int height);
    ~Enemy() override = default;

    void move();
    void someVirtualMethod() override;
    void setPath(const std::vector<std::vector<Cell>>& grid);
    bool hasReachedGoal() const;
    float getLifeBar() const;
};

#endif
