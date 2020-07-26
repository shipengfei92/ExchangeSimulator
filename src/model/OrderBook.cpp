//
// Created by 时鹏飞 on 2020/7/25.
//

#include "OrderBook.h"

PriceLevel &OrderBook::getPriceLevel(uint32_t side_, uint32_t price_) {
    auto& book = side_ == BUY ? _buy: _sell;
    auto it = book.find(price_);
    if (it == book.end()) {
        it = book.insert(PriceLevels::value_type(price_, new PriceLevel(side_, price_))).first;
    }
    return *it->second;
}

void OrderBook::executeOrder(Order *order) {

}

void OrderBook::executeLimitOrder(Order *order) {
    auto price = order->getPrice();
    switch(order->getSide()) {
        case BUY:
            if(_sell.empty() || _sell.begin()->first > price) {
                auto& priceLevel = getPriceLevel(BUY,price);
                priceLevel.addOrder(order);
            } else {

            }
            break;
        case SELL:
            if(_buy.empty() || _buy.rbegin()->first < price) {
                auto priceLevel = getPriceLevel(SELL,price);
                priceLevel.addOrder(order);
            } else {

            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }
}
