#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "Tower.hpp"
#include "Grid.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>  

// Class to create a player with a name, a position, a number of towers and a grid
// The player can add a tower, increment the number of towers, get the position, set the position of a tower, clear the towers, set the name, get the number of towers, get the towers and get the tower textures
// The player can be created with a name, a position, a number of towers and a grid

class Grid;  

class Player {
private:
    std::string name;
    int x, y;
    const std::vector<std::vector<Cell>>& grid;
    std::vector<std::unique_ptr<Tower>> towers;
    std::vector<SDL_Texture*> towerTextures;  
    int numTowers;

public:
    Player(const std::string& name, int x, int y, int numTowers, const std::vector<std::vector<Cell>>& grid, SDL_Renderer* renderer);  
    ~Player();

    std::string getName() const;

    std::pair<int, int> getPosition() const;

    void addTower(int x, int y, SDL_Renderer* renderer, Grid& grid);

    void incrementTowers();

    // void printTowers() const;

    void getPosition(int& x, int& y) const;

    void setPositionTower(int x, int y);

    void clearTowers();

    void setName(const std::string& name);

    int getNumTowers() const;

    const std::vector<std::unique_ptr<Tower>>& getTowers() const;

    const std::vector<SDL_Texture*>& getTowerTextures() const;  
    
};
#endif // PLAYER_HPP
