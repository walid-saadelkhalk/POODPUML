#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>

// Forward declaration
// Wave class
// This class is used to update the observer


class Wave;

class Observer {
public:
    virtual ~Observer() {}
    virtual void update(Wave& wave) = 0;
};


#endif // OBSERVER_HPP