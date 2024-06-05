#include "../hpp_files/Enemy.hpp"
#include <iostream>
#include <queue>

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
        // std::cout << "Enemy moved to: " << posX << ", " << posY << std::endl;
    }
}

void Enemy::someVirtualMethod() {
}

void Enemy::setPath(const std::vector<std::vector<Cell>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<Cell*> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Trouver la première cellule de type 2 en x = 0
    for (int i = 0; i < rows; ++i) {
        if (grid[i][0].typeCell == 2) {
            q.push(const_cast<Cell*>(&grid[i][0]));  // Utiliser const_cast pour enlever la constness
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
                q.push(const_cast<Cell*>(&grid[newX][newY]));  // Utiliser const_cast pour enlever la constness
                visited[newX][newY] = true;
            }
        }
    }
}

bool Enemy::hasReachedGoal() const {
    return currentStep >= path.size();
}
