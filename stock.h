#ifndef __STOCK_H__
#define __STOCK_H__

#include <string>
#include <vector>
#include "subject.h"

class Stock : public Subject {
    float pps; // price per share (market value)
    std::string name;
    std::string abrv;
    std::string desc;
    std::vector<float> prices;
    std::vector<float> changes;
  public:
    Stock(float startingPrice, std::string name, std::string abrv, std::string desc);
    std::vector<float>& getState();
    void setState(float state);
    float getPrice();
    std::string getNameAbrv();
    std::string getDescription();
};

#endif