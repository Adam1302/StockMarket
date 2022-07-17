#include <iostream>

#include "stockTrader.h"
#include "stock.h"

using namespace std;

StockTrader::StockTrader(Stock* st, string name, float balance, int shares): subject{st}, name{name}, balance{balance} {
    subject->attach(this);
}

CompulsiveTrader::CompulsiveTrader(Stock* subject, std::string name, float balance, int shares) :
    StockTrader{subject, name, balance, shares} {}
PragmaticTrader::PragmaticTrader(Stock* subject, std::string name, float balance, int shares) :
    StockTrader{subject, name, balance, shares} {}

StockTrader::~StockTrader() {
    subject->detach(this);
}

void CompulsiveTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (change > 0 && balance >= newPrice) {
        cout << name << ": Buying" << endl;
        balance -= newPrice;
        ++shares;
    } else if (change < 0 && shares > 0) {
        cout << name << ": Selling" << endl;
        balance += newPrice;
        --shares;
    } else {
        cout << name << ": Waiting" << endl;
    }
    cout << name << "'s Balance: $" << balance << endl << endl;
    cout << name << "'s Share Count: " << shares << endl  << endl;
    cout << name << "'s Assets: $" << (balance + (shares*newPrice)) << endl << endl;
}

void PragmaticTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (change > 0 && shares > 0) {
        cout << name << ": Selling" << endl;
        balance += newPrice;
        --shares;
    } else if (change < 0 && balance >= newPrice) {
        cout << name << ": Buying" << endl;
        balance -= newPrice;
        ++shares;
    } else {
        cout << name << ": Waiting" << endl;
    }
    cout << name << "'s Balance: $" << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << (balance + (shares*newPrice)) << endl << endl;
}