#ifndef ENTITIES_HPP
#define ENTITIES_HPP

// This class is used to create the entities of the game
// The entities are created with a position and a death status
// The entities are created with a position in x and y

class Entities {
public:
    int posX;
    int posY;
    bool death;

    Entities(int x, int y);
    virtual ~Entities() = default;

    virtual void someVirtualMethod() = 0; 
};

#endif 
