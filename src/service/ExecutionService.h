#pragma once

#include <boost/log/trivial.hpp>
#include <string>
#include <map>

#include "../utils/Utils.h"
#include "../model/OrderBook.h"
#include "OrderBookService.h"

using namespace std;

class ExecutionService {
private:
    OrderBookService* _orderBookService;

    ExecutionService () {
        _orderBookService = &OrderBookService::getInstance();
    }
    ExecutionService(const ExecutionService&) = delete;
    ExecutionService(ExecutionService&& ) = delete;
    ExecutionService operator=(const ExecutionService&) = delete;

public:
    static ExecutionService& getInstance() {
        static ExecutionService executionService;
        return executionService;
    }

    void processOrder(const string& order);
    void processLimitOrder(Order* order);
    void processMarketOrder(Order* order);
    void processLimitGTCOrder(Order* order);
    void processLimitFOKOrder(Order* order);
    void processLimitIOCOrder(Order* order);

};