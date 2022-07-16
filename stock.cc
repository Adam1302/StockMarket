#include "stock.h"

using namespace std;

Stock::Stock(float startingPrice, std::string name, std::string abrv) :
    pps{startingPrice}, name{name}, abrv{abrv}, prices{}, changes{} {
        prices.emplace_back(startingPrice);
    }

float Stock::getState() {
    return changes[changes.size() - 1];
}

void Stock::setState(float state) {
    changes.emplace_back(state);
    prices.emplace_back(pps + state);
    notifyObservers();
}