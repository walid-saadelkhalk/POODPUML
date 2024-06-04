#include "./logic_game/hpp_files/player.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

Player::Player(std::string name, int x, int y, int numTowers, const std::vector<std::vector<Cell>>& grid) : name(name), x(x), y(y), numTowers(numTowers),grid(grid) {
    std::cout << "Welcome " << name << " !" << std::endl;
}

Player::~Player() {
    std::cout << "Goodbye " << name << " !" << std::endl;
}

std::pair<int, int> Player::getPosition() const {
    return std::make_pair(x, y);
}

std::string Player::getName() const {
    return name;
}

void Player::addTower(int x, int y, SDL_Renderer* renderer) {
    towers.push_back(std::make_unique<Tower>(x, y, 10.0f, 100.0f, 0, 10.0, false, 1));
    std::cout << "Tower added at position (" << x << ", " << y << ")" << std::endl;
}

void Player::getPosition(int& x, int& y) const {
    x = this->x;
    y = this->y;
}

void Player::setPositionTower(int x, int y) {
    towers.back()->setPosition(x, y);
}

const std::vector<std::unique_ptr<Tower>>& Player::getTowers() const {
    return towers;
}
