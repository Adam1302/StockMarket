#ifndef __STOCKTRADER_H__
#define __STOCKTRADER_H__

#include <string>
#include "observer.h"

class Stock;

class StockTrader : public Observer {
  protected:
    Stock* subject;
    std::string name;
    float balance;
    int shares;
  public:
    StockTrader(Stock* subject, std::string name, float balance, int shares);
    //void notify();
    ~StockTrader();
};

class CompulsiveTrader : public StockTrader { // Sells when it goes down, buys when it goes up
  public:
    CompulsiveTrader(Stock* subject, std::string name, float balance, int shares);
    void notify();
    ~CompulsiveTrader() {};
};

class PragmaticTrader : public StockTrader { // Sells when it goes up, buys when it goes down
  public:
    PragmaticTrader(Stock* subject, std::string name, float balance, int shares);
    void notify();
    ~PragmaticTrader() {};
};

class PatientTrader : public StockTrader { // Buys when it goes down 3 days in a row, sells when it goes up 3 days in a row
  public:
    PatientTrader(Stock* subject, std::string name, float balance, int shares);
    void notify();
    ~PatientTrader() {};
};

class SumTrader : public StockTrader { // Sells when net 3-day change is down, buys when net 3-day change is up
  public:
    SumTrader(Stock* subject, std::string name, float balance, int shares);
    void notify();
    ~SumTrader() {};
};

class RandomTrader : public StockTrader { // Buys and sells randomly
  public:
    RandomTrader(Stock* subject, std::string name, float balance, int shares);
    void notify();
    ~RandomTrader() {};
};

#endif