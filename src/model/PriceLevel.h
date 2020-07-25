#pragma once

#include <cstdint>

class OrderBook;

class PriceLevel {
private:
    const uint32_t _side;
    const uint32_t _price;
    OrderBook& _orderBook;

public:

    PriceLevel(uint32_t side_, uint32_t price_, OrderBook &orderBook_);

};