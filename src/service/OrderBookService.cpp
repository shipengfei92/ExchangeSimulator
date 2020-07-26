#include "OrderBookService.h"

#include <iostream>

OrderBook *OrderBookService::getOrderBook(const string &symbol) {
    BOOST_LOG_TRIVIAL(info) << "getOrderBook for symbol: " << symbol <<  endl;

    auto it = _orderBookMap.find(symbol);
    if (it == _orderBookMap.end()) {
        it = _orderBookMap.insert(map<string,OrderBook*>::value_type(symbol, new OrderBook())).first;
    }
    return it->second;
}

void OrderBookService::executeLimitGTCOrder(Order *order) {
    auto orderBook = getOrderBook(order->getSymbol());
    auto price = order->getPrice();
    switch(order->getSide()) {
        case BUY:
            if(orderBook->getSellPriceLevels().empty() ||
            orderBook->getSellPriceLevels().begin()->first > price) {
                auto& priceLevel = orderBook->getPriceLevel(BUY,price);
                priceLevel.addOrder(order);
            } else {

            }
            break;
        case SELL:
            if(orderBook->getBuyPriceLevels().empty() ||
            orderBook->getBuyPriceLevels().rbegin()->first < price) {
                auto priceLevel = orderBook->getPriceLevel(SELL,price);
                priceLevel.addOrder(order);
            } else {

            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }
}

void OrderBookService::executeLimitIOCOrder(Order *order) {

}

void OrderBookService::executeLimitFOKOrder(Order *order) {

}

void OrderBookService::executeMarketOrder(Order *order) {

}