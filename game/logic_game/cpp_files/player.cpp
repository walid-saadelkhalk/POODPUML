#include "./logic_game/hpp_files/player.hpp"
#include <iostream>

Player::Player(std::string name) : name(name) {
    std::cout << "Welcome" << name << " !" << std::endl;
}

std::string Player::getName() const {
    return name;
}

void Player::selectedTower(int x, int y) {
    // towerX = x;
    // towerY = y;
    // std::cout << "Tower selected at position (" << x << ", " << y << ")" << std::endl;
}

void Player::moveTower(int x, int y) {
    // towerX = x;
    // towerY = y;
    // std::cout << "Tower moved to position (" << x << ", " << y << ")" << std::endl;
}