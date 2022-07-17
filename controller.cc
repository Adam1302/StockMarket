#include <iostream>

#include "controller.h"
#include "observer.h"
#include "stockTrader.h"
#include "subject.h"
#include "stock.h"
//#include "observer.h"

using namespace std;

Controller::Controller(istream& in, ostream& out) : in{in}, out{out} {}

float Controller::getChanges() {
    return (((float) rand() / RAND_MAX) - 0.5);
}

void Controller::run() {
    out << "Welcome to the Stock Market" << endl;
    srand(time( NULL ));

    Stock* s1 = new Stock{40, "Aerotyne International", "ART"};

    Observer* ob1 = new CompulsiveTrader{s1, "Adam", 1000.00, 10};
    Observer* ob2 = new PragmaticTrader{s1, "Charles", 1000.00, 10};

    for (int i = 1; i <= 100; ++i) {
        out << "Day " << i << endl;

        float changeToday = getChanges();
        float priceToday = s1->getPrice() + changeToday;
        out << "Stock Price: $" << priceToday << "/share (";
        (changeToday >= 0)? out << "+" : out << "-";
        out << "$" << abs(changeToday) << ")" << endl;
        s1->setState(changeToday);
    }
}