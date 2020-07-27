#include "OrderBookService.h"

#include <iostream>

OrderBook *OrderBookService::getOrderBook(const string &symbol) {
    auto it = _orderBookMap.find(symbol);
    if (it == _orderBookMap.end()) {
        it = _orderBookMap.insert(map<string,OrderBook*>::value_type(symbol, new OrderBook())).first;
    }
    return it->second;
}

void OrderBookService::executeLimitGTCOrder(Order *order) {
    auto orderBook = getOrderBook(order->getSymbol());
    auto price = order->getPrice();
    auto cumQuantity = order->getCumQuantity();
    auto quantity = order->getQuantity() - cumQuantity;
    switch(order->getSide()) {
        case BUY:
            if(orderBook->getSellPriceLevels().empty() ||
            orderBook->getSellPriceLevels().begin()->first > price) {
                auto& priceLevel = orderBook->getPriceLevel(BUY,price);
                priceLevel.addOrder(order);
            } else {
                auto sellBook = orderBook->getSellPriceLevels();
                auto it = sellBook.begin();
                while(quantity > 0 && it != sellBook.end() && it->first<= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(SELL, it->first);
                        ++it;
                    }
                }
                if (quantity > 0) {
                    auto& priceLevel = orderBook->getPriceLevel(BUY,price);
                    priceLevel.addOrder(order);
                }
            }
            break;
        case SELL:
            if(orderBook->getBuyPriceLevels().empty() ||
            orderBook->getBuyPriceLevels().rbegin()->first < price) {
                auto& priceLevel = orderBook->getPriceLevel(SELL,price);
                priceLevel.addOrder(order);
            } else {
                auto buyBook = orderBook->getBuyPriceLevels();
                auto it = buyBook.end();
                --it;
                while(quantity > 0 && it != buyBook.begin() && it->first>= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(BUY, it->first);
                        --it;
                    }
                }
                if (quantity < it->second->getQuantity()) {
                    it->second->executeOrder(order);
                    quantity = 0;
                } else {
                    quantity -= it->second->getQuantity();
                    cumQuantity += it->second->getQuantity();
                    order->setCumQuantity(cumQuantity);
                    orderBook->removePriceLevel(BUY, it->first);
                }
                if (quantity > 0) {
                    auto& priceLevel = orderBook->getPriceLevel(SELL,price);
                    priceLevel.addOrder(order);
                }
            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }
}

void OrderBookService::executeLimitIOCOrder(Order *order) {
    auto orderBook = getOrderBook(order->getSymbol());
    auto price = order->getPrice();
    auto cumQuantity = order->getCumQuantity();
    auto quantity = order->getQuantity() - cumQuantity;
    switch(order->getSide()) {
        case BUY:
            if(orderBook->getSellPriceLevels().empty() ||
               orderBook->getSellPriceLevels().begin()->first > price) {
                return;
            } else {
                auto sellBook = orderBook->getSellPriceLevels();
                auto it = sellBook.begin();
                while(quantity > 0 && it != sellBook.end() && it->first<= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(SELL, it->first);
                        ++it;
                    }
                }
            }
            break;
        case SELL:
            if(orderBook->getBuyPriceLevels().empty() ||
               orderBook->getBuyPriceLevels().rbegin()->first < price) {
                return;
            } else {
                auto buyBook = orderBook->getBuyPriceLevels();
                auto it = buyBook.end();
                --it;
                while(quantity > 0 && it != buyBook.begin() && it->first>= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(BUY, it->first);
                        --it;
                    }
                }
                if (quantity < it->second->getQuantity()) {
                    it->second->executeOrder(order);
                    quantity = 0;
                } else {
                    quantity -= it->second->getQuantity();
                    cumQuantity += it->second->getQuantity();
                    order->setCumQuantity(cumQuantity);
                    orderBook->removePriceLevel(BUY, it->first);
                }
            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }
}

void OrderBookService::executeLimitFOKOrder(Order *order) {
    auto orderBook = getOrderBook(order->getSymbol());
    auto price = order->getPrice();
    auto cumQuantity = order->getCumQuantity();
    auto quantity = order->getQuantity() - cumQuantity;
    switch(order->getSide()) {
        case BUY:
            if(orderBook->getSellPriceLevels().empty() ||
               orderBook->getSellPriceLevels().begin()->first > price) {
                return;
            } else {
                auto sellBook = orderBook->getSellPriceLevels();
                auto it = sellBook.begin();
                uint32_t tmpQuantity = 0;
                while(it != sellBook.end() && it->first<= price) {
                    tmpQuantity += it->second->getQuantity();
                    ++it;
                }
                if (tmpQuantity < quantity) return;
                it = sellBook.begin();
                while(quantity > 0 && it != sellBook.end() && it->first<= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(SELL, it->first);
                        ++it;
                    }
                }
            }
            break;
        case SELL:
            if(orderBook->getBuyPriceLevels().empty() ||
               orderBook->getBuyPriceLevels().rbegin()->first < price) {
                return;
            } else {
                auto buyBook = orderBook->getBuyPriceLevels();
                auto it = --buyBook.end();
                uint32_t tmpQuantity = 0;
                while(it != buyBook.begin() && it->first>= price) {
                    tmpQuantity += it->second->getQuantity();
                    --it;
                }
                tmpQuantity += it->second->getQuantity();
                if (tmpQuantity < quantity) return;

                it = --buyBook.end();
                while(quantity > 0 && it != buyBook.begin() && it->first>= price) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(BUY, it->first);
                        --it;
                    }
                }
                if (quantity < it->second->getQuantity()) {
                    it->second->executeOrder(order);
                    quantity = 0;
                } else {
                    quantity -= it->second->getQuantity();
                    cumQuantity += it->second->getQuantity();
                    order->setCumQuantity(cumQuantity);
                    orderBook->removePriceLevel(BUY, it->first);
                }
            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }
}

void OrderBookService::executeMarketOrder(Order *order) {

    auto orderBook = getOrderBook(order->getSymbol());
    auto cumQuantity = order->getCumQuantity();
    auto quantity = order->getQuantity() - cumQuantity;
    switch(order->getSide()) {
        case BUY:
            if(!orderBook->getSellPriceLevels().empty())
            {
                auto sellBook = orderBook->getSellPriceLevels();
                auto it = sellBook.begin();
                while(quantity > 0 && it != sellBook.end()) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(SELL, it->first);
                        ++it;
                    }
                }
            }

            if (quantity > 0) {
                auto& priceLevel = orderBook->getBestPriceLevel(BUY);
                priceLevel.addOrder(order);
            }
            break;
        case SELL:
            if(!orderBook->getBuyPriceLevels().empty())
            {
                auto buyBook = orderBook->getBuyPriceLevels();
                auto it = buyBook.end();
                --it;
                while(quantity > 0 && it != buyBook.begin()) {
                    if (quantity < it->second->getQuantity()) {
                        it->second->executeOrder(order);
                        quantity = 0;
                    } else {
                        quantity -= it->second->getQuantity();
                        cumQuantity += it->second->getQuantity();
                        order->setCumQuantity(cumQuantity);
                        orderBook->removePriceLevel(BUY, it->first);
                        --it;
                    }
                }
                if (quantity < it->second->getQuantity()) {
                    it->second->executeOrder(order);
                    quantity = 0;
                } else {
                    quantity -= it->second->getQuantity();
                    cumQuantity += it->second->getQuantity();
                    order->setCumQuantity(cumQuantity);
                    orderBook->removePriceLevel(BUY, it->first);
                }
            }
            if (quantity > 0) {
                auto& priceLevel = orderBook->getBestPriceLevel(SELL);
                priceLevel.addOrder(order);
            }

            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unsupported side." << endl;
    }

}

void OrderBookService::clearOrderBooks() {
    _orderBookMap.clear();
}
