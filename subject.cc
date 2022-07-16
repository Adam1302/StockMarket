#include <algorithm>
#include "subject.h"
#include "observer.h"

using namespace std;

Subject::Subject() : observers{} {}

void Subject::attach(Observer* ob) {
    observers.emplace_back(ob);
}

void Subject::detach(Observer* ob) {
    observers.erase(std::remove(observers.begin(), observers.end(), ob), observers.end());
}

void Subject::notifyObservers() {
    for (auto& ob: observers) {
        ob->notify();
    }
}

Subject::~Subject() {};