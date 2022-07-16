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

    Stock* s1 = new Stock{0.5, "Aerotyne International", "ART"};

    Observer* ob1 = new CompulsiveTrader{s1, "Adam"};
    Observer* ob2 = new PragmaticTrader{s1, "Charles"};

    for (int i = 1; i <= 5; ++i) {
        out << "Day " << i << endl;

        float priceToday = getChanges();
        out << "Stock Price: " << priceToday << endl;
        s1->setState(priceToday);
    }
}