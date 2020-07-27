#include "OrderBook.h"

PriceLevel &OrderBook::getPriceLevel(uint32_t side, uint32_t price) {
    auto& book = side == BUY ? _buy: _sell;
    auto it = book.find(price);
    if (it == book.end()) {
        it = book.insert(PriceLevels::value_type(price, new PriceLevel(side, price))).first;
    }
    return *it->second;
}

PriceLevel &OrderBook::getBestPriceLevel(uint32_t side) {
    return side == BUY ? *_buy.rbegin()->second : *_sell.begin()->second;
}

void OrderBook::removePriceLevel(uint32_t side, uint32_t price) {
    auto& book = side == BUY ? _buy: _sell;
    auto it = book.find(price);
    if (it != book.end()) {
        book.erase(it);
    }
}

void OrderBook::clearOrderBook() {
    _buy.clear();
    _sell.clear();
}
