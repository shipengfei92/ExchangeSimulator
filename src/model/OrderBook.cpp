//
// Created by 时鹏飞 on 2020/7/25.
//

#include "OrderBook.h"

PriceLevel &OrderBook::getPriceLevel(uint32_t side_, uint32_t price_) {
    auto book = side_ == 0 ? _buy: _sell;
    auto it = book.find(price_);
    if (it == book.end()) {
        it = book.insert(PriceLevels::value_type(price_, new PriceLevel(side_, price_, *this))).first;
    }
    return *it->second;
}
