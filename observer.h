#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>

class Observer {
  public:
    virtual void notify() = 0;
    virtual const std::string getName() = 0;
    virtual const float getAssets() = 0;
    virtual const float getStarting() = 0;
    virtual ~Observer();
};

#endif