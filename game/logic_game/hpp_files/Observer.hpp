#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>


class Wave;

class Observer {
public:
    virtual ~Observer() {}
    virtual void update(Wave& wave) = 0;
};


#endif // OBSERVER_HPP