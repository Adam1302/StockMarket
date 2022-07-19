#include <iostream>
#include <memory>

#include "controller.h"
#include "observer.h"
#include "stockTrader.h"
#include "subject.h"
#include "stock.h"

using namespace std;

Controller::Controller(istream& in, ostream& out) :
    in{in}, out{out}, distribution{0, 5.0} {}

float Controller::getChanges() {
    float num = distribution(generator);
    return num;
}

void Controller::run() {
    out << "Welcome to the Stock Market. The stock in focus is:" << endl << endl;

    unique_ptr<Stock> s1 = make_unique<Stock>(40, "Aerotyne International", "ART");
    
    out << s1->getNameAbrv() << endl << "A cutting edge high-tech firm out of the Midwest awaiting imminent patent approval on the next generation of radar detectors that have both huge military and civilian applications now." << endl << endl;

    unique_ptr<Observer> ob1 = make_unique<CompulsiveTrader>(s1, "Adam", 1000.00, 10);
    unique_ptr<Observer> ob2 = make_unique<PragmaticTrader>(s1, "Charles", 1000.00, 10);
    unique_ptr<Observer> ob3 = make_unique<PatientTrader>(s1, "Ricky", 1000.00, 10);
    unique_ptr<Observer> ob4 = make_unique<SumTrader>(s1, "Stewie", 1000.00, 10);
    unique_ptr<Observer> ob5 = make_unique<RandomTrader>(s1, "Yolanda", 1000.00, 10);

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