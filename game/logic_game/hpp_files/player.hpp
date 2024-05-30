#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

class Player {
private:
    std::string name;
    int x, y;

public:
    Player(const std::string name, int x, int y);

    std::string getName() const;

    std::pair<int, int> getPosition() const;


    void selectedTower(int x, int y);

    void moveTower(int x, int y);
};

#endif // PLAYER_HPP