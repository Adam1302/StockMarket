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
PatientTrader::PatientTrader(Stock* subject, std::string name, float balance, int shares) :
    StockTrader{subject, name, balance, shares} {}
SumTrader::SumTrader(Stock* subject, std::string name, float balance, int shares) :
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
    cout << name << "'s Balance: $" << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
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

void PatientTrader::notify() { // CHANGE
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    // float change = changes[changes.size() - 1];

    if (changes.size() >= 3 && changes.size() % 3 == 0) {
        float change1 = changes[changes.size() - 1];
        float change2 = changes[changes.size() - 2];
        float change3 = changes[changes.size() - 3];
        if (change1 > 0 && change2 > 0 && change3 > 0 && shares > 0) {
            cout << name << ": Selling" << endl;
            balance += newPrice;
            --shares;
        } else if (change1 < 0 && change2 < 0 && change3 < 0 && balance >= newPrice) {
            cout << name << ": Buying" << endl;
            balance -= newPrice;
            ++shares;
        }
    } else {
        cout << name << ": Waiting" << endl;
    }
    cout << name << "'s Balance: $" << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << (balance + (shares*newPrice)) << endl << endl;
}

void SumTrader::notify() { // CHANGE
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (changes.size() >= 3 && changes.size() % 3 == 0) {
        float change = changes[changes.size() - 1] + changes[changes.size() - 2] + changes[changes.size() - 3];
        if (change > 0 && shares > 0) {
            cout << name << ": Selling" << endl;
            balance += newPrice;
            --shares;
        } else if (change < 0 && balance >= newPrice) {
            cout << name << ": Buying" << endl;
            balance -= newPrice;
            ++shares;
        }
    } else {
        cout << name << ": Waiting" << endl;
    }
    cout << name << "'s Balance: $" << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << (balance + (shares*newPrice)) << endl << endl;
}