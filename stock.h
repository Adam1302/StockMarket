#ifndef __STOCK_H__
#define __STOCK_H__

#include <string>
#include <vector>
#include "subject.h"

class Stock : public Subject {
    double pps; // price per share (market value)
    std::string name;
    std::string abrv;
    std::vector<float> prices;
    std::vector<float> changes;
  public:
    Stock(float startingPrice, std::string name, std::string abrv);
    float getState();
    void setState(float state);
};

#endif