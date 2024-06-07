#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>
#include <algorithm>

// Forward declaration
// Observer interface
// This class is used to update the observer

class Observer;

// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

#endif // SUBJECT_HPP