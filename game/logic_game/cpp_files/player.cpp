#include "./logic_game/hpp_files/player.hpp"
#include <iostream>

Player::Player(std::string name,int x, int y) : name(name), x(x), y(y){
    std::cout << "Welcome" << name << " !" << std::endl;
}

std::pair<int, int> Player::getPosition() const {
    return std::make_pair(x, y);
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