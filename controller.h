#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <iostream>
#include <random>

class Controller {
    std::istream& in;
    std::ostream& out;

    std::normal_distribution<float> distribution;
    std::default_random_engine generator;

    float getChanges();

  public:
    Controller(std::istream&, std::ostream&);

    void run();
};

#endif