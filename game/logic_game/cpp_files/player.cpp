#include "./logic_game/hpp_files/Player.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <random>

// This file is a class that creates a player
// The player can be created with a name, a position, a number of towers, a grid and a renderer
// The player can be displayed with the name, the position, the number of towers, the grid and the renderer
// The player can add a tower, increment the number of towers, get the position, get the number of towers, get the towers, get the tower textures, clear the towers, set the name and set the position of the tower

Player::Player(const std::string& name, int x, int y, int numTowers, const std::vector<std::vector<Cell>>& grid, SDL_Renderer* renderer)  // Correction
    : name(name), x(x), y(y), numTowers(numTowers), grid(grid) {
    std::cout << "Welcome !" << std::endl;
    
    for (int i = 0; i < numTowers; ++i) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/images/Mordor/Tower.jpg");
        if (texture) {
            towerTextures.push_back(texture);
        } else {
            std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        }
    }
}

Player::~Player() {
    for (auto texture : towerTextures) {
        SDL_DestroyTexture(texture);
    }
    std::cout << "Goodbye " << name << " !" << std::endl;
}

std::pair<int, int> Player::getPosition() const {
    return std::make_pair(x, y);
}

std::string Player::getName() const {
    return name;
}

void Player::addTower(int x, int y, SDL_Renderer* renderer, Grid& grid) {
    if (numTowers > 0) {
        if (grid.isCellEmpty(x, y)) {
            towers.push_back(std::make_unique<Tower>(x, y, 15.0f, 100.0f, 0, 10.0, false, 1, 3));
            grid.setCellTexture(x, y, nullptr);
            --numTowers;
            std::cout << "Tower added at position (" << x << ", " << y << ")" << std::endl;
        } else {
            std::cout << "Cell is already occupied." << std::endl;
        }
    } else {
        std::cout << "No more towers available to add." << std::endl;
    }
}

void Player::incrementTowers() {
    ++numTowers;
    std::cout << "One tower added. Total towers available: " << numTowers << std::endl;
}

void Player::getPosition(int& x, int& y) const {
    x = this->x;
    y = this->y;
}

void Player::setPositionTower(int x, int y) {
    towers.back()->setPosition(x, y);
}

int Player::getNumTowers() const {
    return numTowers;
}

const std::vector<std::unique_ptr<Tower>>& Player::getTowers() const {
    return towers;
}

const std::vector<SDL_Texture*>& Player::getTowerTextures() const {
    return towerTextures;
}

void Player::clearTowers() {
    std::cout << "Clearing towers..." << std::endl;
    for (auto& tower : towers) {
        if (tower->texture) {
            SDL_DestroyTexture(tower->texture);
            tower->texture = nullptr;
        }
    }
    towers.clear();
    numTowers = 0;
    std::cout << "Towers cleared." << std::endl;
}

void Player::setName(const std::string& name) {
    this->name = name;
}

