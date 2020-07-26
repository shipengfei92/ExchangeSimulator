#pragma once

#include <list>
#include "Order.h"

class PriceLevel {
private:
    const uint32_t _side;
    const uint32_t _price;
    uint32_t _quantity;
    list<Order*> _orderList;

public:
    PriceLevel(uint32_t side, uint32_t price);
    void addOrder(Order* order);
    void removeOrder(Order* order);
    void executeOrder(Order* order);
    uint32_t getQuantity() const;

};