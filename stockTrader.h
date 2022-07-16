#ifndef __STOCKTRADER_H__
#define __STOCKTRADER_H__

#include <string>
#include "observer.h"

class Stock;

class StockTrader : public Observer {
  protected:
    Stock* subject;
    std::string name;
  public:
    StockTrader(Stock* subject, std::string name);
    //void notify();
    ~StockTrader();
};

class CompulsiveTrader : public StockTrader {
  public:
    CompulsiveTrader(Stock* subject, std::string name);
    void notify();
    ~CompulsiveTrader() {};
};

class PragmaticTrader : public StockTrader {
  public:
    PragmaticTrader(Stock* subject, std::string name);
    void notify();
    ~PragmaticTrader() {};
};

#endif