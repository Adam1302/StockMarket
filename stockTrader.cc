#include <iomanip>

#include "stockTrader.h"
#include "stock.h"

using namespace std;

StockTrader::StockTrader(ostream& out, unique_ptr<Stock>& st, string name, float balance, int shares):
        out{out}, subject{st}, name{name}, balance{balance}, shares{shares}, startingBalance{ balance+ (shares * subject->getPrice()) } {
    subject->attach(this);
    srand(time(0));
}

const std::string StockTrader::getName() { return name; }
const float StockTrader::getAssets() { return balance + (shares * (subject->getPrice())); }
const float StockTrader::getStarting() { return startingBalance; }

CompulsiveTrader::CompulsiveTrader(ostream& out, unique_ptr<Stock>& subject, std::string name, float balance, int shares) :
    StockTrader{out, subject, name, balance, shares} {}
PragmaticTrader::PragmaticTrader(ostream& out, unique_ptr<Stock>& subject, std::string name, float balance, int shares) :
    StockTrader{out, subject, name, balance, shares} {}
PatientTrader::PatientTrader(ostream& out, unique_ptr<Stock>& subject, std::string name, float balance, int shares) :
    StockTrader{out, subject, name, balance, shares} {}
SumTrader::SumTrader(ostream& out, unique_ptr<Stock>& subject, std::string name, float balance, int shares) :
    StockTrader{out, subject, name, balance, shares} {}
RandomTrader::RandomTrader(ostream& out, unique_ptr<Stock>& subject, std::string name, float balance, int shares) :
    StockTrader{out, subject, name, balance, shares} {}

StockTrader::~StockTrader() {}

int StockTrader::getShares(int max) {
    int num1 = (rand() % max) + 1;
    int num2 = (rand() % max) + 1;

    return min(num1, num2);
}

void CompulsiveTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (newPrice == 0) return;

    int maxSharePurchase = balance / newPrice;

    if (change > 0 && maxSharePurchase > 0) {
        int sharePurchaseCount = getShares(maxSharePurchase);

        cout << name << ": Buying " << sharePurchaseCount << " share(s)." << endl;
        balance -= (newPrice * sharePurchaseCount);
        shares += sharePurchaseCount;
    } else if (change < 0 && shares > 0) {
        int shareSellingCount = getShares(shares);

        cout << name << ": Selling " << shareSellingCount << " share(s)."  << endl;
        balance += (newPrice * shareSellingCount);
        shares -= shareSellingCount;
    } else {
        cout << name << ": Waiting" << endl;
    }

    cout << name << "'s Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << fixed << setprecision(2) << (balance + (shares*newPrice)) << endl << endl;
}

void PragmaticTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (newPrice == 0) return;

    int maxSharePurchase = balance / newPrice;

    if (change > 0 && shares > 0) {
        int shareSellingCount = getShares(shares);

        cout << name << ": Selling " << shareSellingCount << " share(s)."  << endl;
        balance += (newPrice * shareSellingCount);
        shares -= shareSellingCount;
    } else if (change < 0 && balance >= newPrice) {
        int sharePurchaseCount = getShares(maxSharePurchase);

        cout << name << ": Buying " << sharePurchaseCount << " share(s)." << endl;
        balance -= (newPrice * sharePurchaseCount);
        shares += sharePurchaseCount;
    } else {
        cout << name << ": Waiting" << endl;
    }

    cout << name << "'s Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << fixed << setprecision(2) << (balance + (shares*newPrice)) << endl << endl;
}

void PatientTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();

    if (newPrice == 0) return;

    int maxSharePurchase = balance / newPrice;

    if (changes.size() >= 3 && changes.size() % 3 == 0) {
        float change1 = changes[changes.size() - 1];
        float change2 = changes[changes.size() - 2];
        float change3 = changes[changes.size() - 3];
        if (change1 > 0 && change2 > 0 && change3 > 0 && shares > 0) {
            int shareSellingCount = getShares(shares);

            cout << name << ": Selling " << shareSellingCount << " share(s)."  << endl;
            balance += (newPrice * shareSellingCount);
            shares -= shareSellingCount;
        } else if (change1 < 0 && change2 < 0 && change3 < 0 && balance >= newPrice) {
            int sharePurchaseCount = getShares(maxSharePurchase);

            cout << name << ": Buying " << sharePurchaseCount << " share(s)." << endl;
            balance -= (newPrice * sharePurchaseCount);
            shares += sharePurchaseCount;
        }
    } else {
        cout << name << ": Waiting" << endl;
    }

    cout << name << "'s Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << fixed << setprecision(2) << (balance + (shares*newPrice)) << endl << endl;
}

void SumTrader::notify() {
    std::vector<float> changes = subject->getState();

    float newPrice = subject->getPrice();
    float change = changes[changes.size() - 1];

    if (newPrice == 0) return;

    int maxSharePurchase = balance / newPrice;

    if (changes.size() >= 3 && changes.size() % 3 == 0) {
        float change = changes[changes.size() - 1] + changes[changes.size() - 2] + changes[changes.size() - 3];
        if (change > 0 && shares > 0) {
            int shareSellingCount = getShares(shares);

            cout << name << ": Selling " << shareSellingCount << " share(s)."  << endl;
            balance += (newPrice * shareSellingCount);
            shares -= shareSellingCount;
        } else if (change < 0 && balance >= newPrice) {
            int sharePurchaseCount = getShares(maxSharePurchase);

            cout << name << ": Buying " << sharePurchaseCount << " share(s)." << endl;
            balance -= (newPrice * sharePurchaseCount);
            shares += sharePurchaseCount;
        }
    } else {
        cout << name << ": Waiting" << endl;
    }

    cout << name << "'s Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << fixed << setprecision(2) << (balance + (shares*newPrice)) << endl << endl;
}

void RandomTrader::notify() { // CHANGE
    float newPrice = subject->getPrice();

    if (newPrice == 0) return;

    int maxSharePurchase = balance / newPrice;

    int chance = (rand() % 3) + 1;
    if (chance == 1 && shares > 0) {
        int shareSellingCount = getShares(shares);

        cout << name << ": Selling " << shareSellingCount << " share(s)."  << endl;
        balance += (newPrice * shareSellingCount);
        shares -= shareSellingCount;
    } else if (chance == 2 && balance >= newPrice) {
        int sharePurchaseCount = getShares(maxSharePurchase);

        cout << name << ": Buying " << sharePurchaseCount << " share(s)." << endl;
        balance -= (newPrice * sharePurchaseCount);
        shares += sharePurchaseCount;
    } else {
        cout << name << ": Waiting" << endl;
    }

    cout << name << "'s Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << name << "'s Share Count: " << shares << endl;
    cout << name << "'s Assets: $" << fixed << setprecision(2) << (balance + (shares*newPrice)) << endl << endl;
}