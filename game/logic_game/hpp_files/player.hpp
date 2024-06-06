#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "Tower.hpp"
#include "Grid.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>  // Ajouté pour SDL_Texture

class Grid;  

class Player {
private:
    std::string name;
    int x, y;
    const std::vector<std::vector<Cell>>& grid;
    std::vector<std::unique_ptr<Tower>> towers;
    std::vector<SDL_Texture*> towerTextures;  // Ajouté pour stocker les textures
    int numTowers;

public:
    Player(const std::string& name, int x, int y, int numTowers, const std::vector<std::vector<Cell>>& grid, SDL_Renderer* renderer);  // Correction
    ~Player();

    std::string getName() const;

    std::pair<int, int> getPosition() const;

    void addTower(int x, int y, SDL_Renderer* renderer, Grid& grid);

    void incrementTowers();

    // void printTowers() const;

    void getPosition(int& x, int& y) const;

    void setPositionTower(int x, int y);

    int getNumTowers() const;

    const std::vector<std::unique_ptr<Tower>>& getTowers() const;

    const std::vector<SDL_Texture*>& getTowerTextures() const;  // Nouvelle méthode
};

#endif // PLAYER_HPP
