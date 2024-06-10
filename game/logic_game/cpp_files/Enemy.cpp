#include "../hpp_files/Enemy.hpp"
#include <iostream>
#include <queue>

// This file is a class that creates an enemy
// The enemy can be created with a position, a life bar, a height and a current step
// The enemy can move and set a path

Enemy::Enemy(int x, int y, float lifeBar, int height)
    : Entities(x, y), lifeBar(lifeBar), height(height), currentStep(0) {
    posX = x;
    posY = y;
}

void Enemy::move() {
    if (currentStep < path.size()) {
        posX = path[currentStep]->heightCell;
        posY = path[currentStep]->widthCell;
        currentStep++;
    }
}

void Enemy::someVirtualMethod() {
}

void Enemy::setPath(const std::vector<std::vector<Cell>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<Cell*> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        if (grid[i][0].typeCell == 2) {
            q.push(const_cast<Cell*>(&grid[i][0]));
            visited[i][0] = true;
            break;
        }
    }

    std::vector<int> dirX = {0, 0, -1, 1};
    std::vector<int> dirY = {-1, 1, 0, 0};

    while (!q.empty()) {
        Cell* current = q.front();
        q.pop();
        path.push_back(current);

        if (current->widthCell * 20 >= 1000) {  
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int newX = current->widthCell + dirX[d];
            int newY = current->heightCell + dirY[d];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY] && grid[newX][newY].typeCell == 2) {
                q.push(const_cast<Cell*>(&grid[newX][newY])); 
                visited[newX][newY] = true;
            }
        }
    }
}

bool Enemy::hasReachedGoal() const {
    return currentStep >= path.size();
}

float Enemy::getLifeBar() const {
    return lifeBar;
}   

int Enemy::getTextureIndex() const {
    return textureIndex;
}

void Enemy::setTextureIndex(int index) {
    textureIndex = index;
}


