#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "Tower.hpp"
#include "Grid.hpp"
#include <vector>
#include <memory>

class Player {
private:
    std::string name;
    int x, y;
    const std::vector<std::vector<Cell>>& grid;
    std::vector<std::unique_ptr<Tower>> towers;
    int numTowers;

public:
    Player(const std::string name, int x, int y, int numTowers,const std::vector<std::vector<Cell>>& grid);
    ~Player();

    std::string getName() const;

    std::pair<int, int> getPosition() const;

    void addTower(int x, int y, SDL_Renderer* renderer, Grid& grid);

    void incrementTowers();

    void getPosition(int& x, int& y) const;

    void setPositionTower(int x, int y);

    const std::vector<std::unique_ptr<Tower>>& getTowers() const;

    std::vector<SDL_Texture*> getTowerTextures(SDL_Renderer* renderer) const;
};

#endif // PLAYER_HPP
