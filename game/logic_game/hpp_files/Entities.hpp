#ifndef ENTITIES_HPP
#define ENTITIES_HPP

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
