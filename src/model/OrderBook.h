#pragma once

#include "PriceLevel.h"

#include <map>

typedef std::map<int, PriceLevel*, std::less<int>> PriceLevels;

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

    const PriceLevels& getBuyPriceLevels() const { return _buy; }
    const PriceLevels& getSellPriceLevels() const { return _sell; }

};
