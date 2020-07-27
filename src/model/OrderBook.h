#pragma once

#include "PriceLevel.h"

#include <vector>
#include <map>
#include <iostream>
#include <boost/log/trivial.hpp>

using namespace std;

typedef map<uint32_t , PriceLevel*, less<uint32_t>> PriceLevels;

class OrderBook {
private:

    PriceLevels _buy;
    PriceLevels _sell;

    OrderBook(const OrderBook&) = delete;
    OrderBook operator=(const OrderBook&) = delete;
    OrderBook(OrderBook &&) = delete;

public:
    OrderBook() {}

    PriceLevel& getPriceLevel(uint32_t side, uint32_t price);
    PriceLevel& getBestPriceLevel(uint32_t side);

    const PriceLevels& getBuyPriceLevels() const { return _buy; }
    const PriceLevels& getSellPriceLevels() const { return _sell; }

    void clearOrderBook();
    void removePriceLevel(uint32_t side, uint32_t price);

};
