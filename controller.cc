#include <iostream>
#include <iomanip>
#include <memory>
#include <chrono>
#include <thread>

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
    using namespace std::this_thread; // sleep_for
    using namespace std::chrono; // nanoseconds

    out << "Welcome to the Stock Market. The stock in focus is:" << endl << endl;

    unique_ptr<Stock> s1 = make_unique<Stock>(40, "Aerotyne International", "ART");
    
    sleep_for(1s);
    
    out << s1->getNameAbrv() << endl << "A cutting edge high-tech firm out of the Midwest awaiting imminent patent approval on the next generation of radar detectors that have both huge military and civilian applications now." << endl << endl;
    
    sleep_for(5s);

    vector< unique_ptr<Observer> > observerList;

    observerList.emplace_back(make_unique<CompulsiveTrader>(out, s1, "Adam", 1000.00, 10));
    observerList.emplace_back(make_unique<PragmaticTrader>(out, s1, "Charles", 1000.00, 10));
    observerList.emplace_back(make_unique<PatientTrader>(out, s1, "Ricky", 1000.00, 10));
    observerList.emplace_back(make_unique<SumTrader>(out, s1, "Stewie", 1000.00, 10));
    observerList.emplace_back(make_unique<RandomTrader>(out, s1, "Yolanda", 1000.00, 10));

    int i = 1;
    char c;

    out << "Type any character to begin: ";
    in >> c;
    cin.clear();
    cin.ignore(10000, '\n');
    out << endl << endl;
    
    while (true) {
        out << "Day " << i << endl;
        sleep_for(1s);

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
        out << "$" << abs(changeToday) << ")" << endl << endl;

        sleep_for(2s);

        s1->setState(changeToday);

        ++i;
        
        out << "Type 'q' to quit and any other key to continue: ";
        in >> c;

        if (c == 'q' || c == 'Q') { 
            break;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            out << endl;
        }
    }

    out << endl << left << setw(20) << "Final Results:" << setw(25) << "Initial Balance ($)" << setw(25) << "Final Balance ($)" << endl;

    for (auto& o : observerList) {
        out << setw(20) << o->getName() << setw(25) << o->getStarting() << setw(25) << o->getAssets() << endl;
    }


}