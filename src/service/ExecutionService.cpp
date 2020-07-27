#include "ExecutionService.h"

void ExecutionService::processOrder(const string &orderStr) {
    Order * order = Utils::orderParser(orderStr);
    if(order == nullptr) {
        return;
    }
    switch(order->getOrderType()) {
        case OrderType::Limit:
            processLimitOrder(order);
            break;
        case OrderType::Market:
            processMarketOrder(order);
            break;
        default:
            BOOST_LOG_TRIVIAL(error) << "OrderType is not supported." << endl;
    }
}

void ExecutionService::processLimitOrder(Order *order) {
    switch (order->getTif()) {
        case TimeInForce::GTC:
            processLimitGTCOrder(order);
            break;
        case TimeInForce::IOC:
            processLimitIOCOrder(order);
            break;
        case TimeInForce::FOK:
            processLimitFOKOrder(order);
    }
}

void ExecutionService::processMarketOrder(Order *order) {
    _orderBookService->executeMarketOrder(order);
}

void ExecutionService::processLimitGTCOrder(Order *order) {
    _orderBookService->executeLimitGTCOrder(order);
}

void ExecutionService::processLimitFOKOrder(Order *order) {
    _orderBookService->executeLimitFOKOrder(order);
}

void ExecutionService::processLimitIOCOrder(Order *order) {
    _orderBookService->executeLimitIOCOrder(order);
}
