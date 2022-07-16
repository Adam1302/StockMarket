#include <iostream>

#include "stockTrader.h"
#include "stock.h"

using namespace std;

StockTrader::StockTrader(Stock* st, string name): subject{st}, name{name} {
    subject->attach(this);
}

CompulsiveTrader::CompulsiveTrader(Stock* subject, std::string name) : StockTrader{subject, name} {}
PragmaticTrader::PragmaticTrader(Stock* subject, std::string name) : StockTrader{subject, name} {}

StockTrader::~StockTrader() {
    subject->detach(this);
}

void CompulsiveTrader::notify() {
    float change = subject->getState();

    if (change > 0) {
        cout << name << ": Buying" << endl;
    } else if (change < 0) {
        cout << name << ": Selling" << endl;
    } else {
        cout << name << ": Waiting" << endl;
    }
}

void PragmaticTrader::notify() {
    float change = subject->getState();;

    if (change > 0) {
        cout << name << ": Selling" << endl;
    } else if (change < 0) {
        cout << name << ": Buying" << endl;
    } else {
        cout << name << ": Waiting" << endl;
    }
}