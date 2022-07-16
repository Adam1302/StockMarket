#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <iostream>

class Controller {
    std::istream& in;
    std::ostream& out;

    float getChanges();

  public:
    Controller(std::istream&, std::ostream&);

    void run();
};

#endif