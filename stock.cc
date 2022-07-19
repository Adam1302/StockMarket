#include "stock.h"

using namespace std;

Stock::Stock(float startingPrice, std::string name, std::string abrv, std::string desc) :
    pps{startingPrice}, name{name}, abrv{abrv}, desc{desc}, prices{}, changes{} {
        prices.emplace_back(startingPrice);
    }

std::vector<float>& Stock::getState() {
    return changes;
}

void Stock::setState(float state) {
    pps += state;
    if (pps < 0) pps = 0;
    changes.emplace_back(state);
    prices.emplace_back(pps);
    notifyObservers();
}

float Stock::getPrice() { return pps; }

string Stock::getNameAbrv() {
    return name + " (" + abrv + ")";
}

string Stock::getDescription() {
    return desc;
}