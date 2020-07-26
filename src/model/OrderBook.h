#pragma once

#include "PriceLevel.h"

#include <vector>
#include <map>
#include <iostream>
#include <boost/log/trivial.hpp>

using namespace std;

typedef map<uint32_t , PriceLevel*> PriceLevels;

class OrderBook {
private:

    PriceLevels _buy;
    PriceLevels _sell;

    OrderBook(const OrderBook&) = delete;
    OrderBook operator=(const OrderBook&) = delete;
    OrderBook(OrderBook &&) = delete;

public:
    OrderBook() {}
    void executeOrder(Order* order);
    void executeLimitOrder(Order* order);
    void executeMarketOrder(Order* order);

    PriceLevel& getPriceLevel(uint32_t side, uint32_t price);

    const PriceLevels& getBuyPriceLevels() const { return _buy; }
    const PriceLevels& getSellPriceLevels() const { return _sell; }

};
