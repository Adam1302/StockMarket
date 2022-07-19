#include <iostream>

#include "controller.h"
#include "observer.h"
#include "stockTrader.h"
#include "subject.h"
#include "stock.h"

using namespace std;

Controller::Controller(istream& in, ostream& out) : in{in}, out{out} {}

float Controller::getChanges() {
    std::normal_distribution<float> distribution{-4.0, 5.0}; // We will use a normal distribution
        // The mean is -1 since the c++ normal distribution is negatively skewed

    float num = distribution(generator);
    return num;
}

void Controller::run() {
    out << "Welcome to the Stock Market" << endl;

    Stock* s1 = new Stock{40, "Aerotyne International", "ART", "a"};

    // out << s1->getNameAbrv() << endl << "\t" << s1->getDescription() << endl << endl;

    Observer* ob1 = new CompulsiveTrader{s1, "Adam", 1000.00, 10};
    Observer* ob2 = new PragmaticTrader{s1, "Charles", 1000.00, 10};
    Observer* ob3 = new PatientTrader{s1, "Ricky", 1000.00, 10};
    Observer* ob4 = new SumTrader{s1, "Stewie", 1000.00, 10};
    Observer* ob5 = new RandomTrader{s1, "Yolanda", 1000.00, 10};

    for (int i = 1; i <= 35; ++i) {
        out << "Day " << i << endl;

        float changeToday = getChanges();
        float priceToday = s1->getPrice();

        if (changeToday + priceToday < 0) {
            changeToday = 0 - priceToday;
            priceToday = 0;
        } else {
            priceToday += changeToday;
        }

        if (priceToday < 0) priceToday = 0;

        out << s1->getNameAbrv() << ": " << priceToday << "/share (";
        (changeToday >= 0)? out << "+" : out << "-";
        out << "$" << abs(changeToday) << ")" << endl;

        s1->setState(changeToday);
    }
}