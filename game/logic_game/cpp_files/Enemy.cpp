#include "../hpp_files/Enemy.hpp"
#include <queue>

Enemy::Enemy(int x, int y, float lifeBar, int height)
    : Entities(x, y), lifeBar(lifeBar), height(height), currentStep(0) {
}

void Enemy::move() {
    if (currentStep < path.size()) {
        posX = path[currentStep]->widthCell;
        posY = path[currentStep]->heightCell;
        currentStep++;
    }
}

void Enemy::someVirtualMethod() {
    // Implémentez la méthode virtuelle ici
}

void Enemy::setPath(const std::vector<std::vector<Cell*>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<Cell*> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Trouver le point de départ (case 7)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]->typeCell == 7) {
                q.push(grid[i][j]);
                visited[i][j] = true;
                break;
            }
        }
    }

    // BFS pour trouver le chemin
    std::vector<int> dirX = {0, 0, -1, 1};
    std::vector<int> dirY = {-1, 1, 0, 0};

    while (!q.empty()) {
        Cell* current = q.front();
        q.pop();
        path.push_back(current);

        if (current->typeCell == 1) {
            break;  // Arrivée
        }

        for (int d = 0; d < 4; ++d) {
            int newX = current->widthCell + dirX[d];
            int newY = current->heightCell + dirY[d];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY] && (grid[newX][newY]->typeCell == 2 || grid[newX][newY]->typeCell == 1)) {
                q.push(grid[newX][newY]);
                visited[newX][newY] = true;
            }
        }
    }
}
