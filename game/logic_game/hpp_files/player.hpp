#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

class Player {
private:
    std::string name;

public:
    Player(const std::string name);

    std::string getName() const;

    void registerPlayer();

    void selectedTower(int x, int y);

    void moveTower(int x, int y);
};

#endif // PLAYER_HPP