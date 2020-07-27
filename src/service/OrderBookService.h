#pragma once

#include <map>
#include <boost/log/trivial.hpp>
#include "../model/OrderBook.h"

using namespace std;

class OrderBookService {
private:
    map<string,OrderBook*> _orderBookMap;

    OrderBookService() {}
    OrderBookService(const OrderBookService&) = delete;
    OrderBookService(OrderBookService&& ) = delete;
    OrderBookService operator=(const OrderBookService&) = delete;

public:
    static OrderBookService& getInstance() {
        static OrderBookService orderBookService;
        return orderBookService;
    }

    void clearOrderBooks();

    OrderBook* getOrderBook(const string& symbol);
    map<string,OrderBook*> getAllOrderBook() { return _orderBookMap; }

    void executeMarketOrder(Order *order);
    void executeLimitGTCOrder(Order *order);
    void executeLimitIOCOrder(Order *order);
    void executeLimitFOKOrder(Order *order);

};