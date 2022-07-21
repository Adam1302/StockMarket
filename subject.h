#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <memory>
//#include <observer.h>

class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    Subject();
    void attach(Observer*);
    void notifyObservers();
    virtual ~Subject() = 0;
};

#endif