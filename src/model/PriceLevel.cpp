#include "PriceLevel.h"

PriceLevel::PriceLevel(uint32_t side, uint32_t price) :
                _side(side), _price(price), _quantity(0) {}

void PriceLevel::addOrder(Order *order) {
    _orderList.push_back(order);
    _quantity += (order->getQuantity() - order->getCumQuantity());
}

void PriceLevel::removeOrder(Order *order) {
    auto it = find(_orderList.begin(), _orderList.end(), order);
    if(it != _orderList.end()) {
        _orderList.remove(*it);
        _quantity -= ((*it)->getQuantity() - (*it)->getCumQuantity());
    }
}

void PriceLevel::executeOrder(Order *order) {
    auto remainQuantity = order->getQuantity() - order->getCumQuantity();
    auto it = _orderList.begin();
    while(remainQuantity > 0) {
        auto quantity = (*it)->getQuantity() - (*it)->getCumQuantity();
        if (quantity > remainQuantity) {
            (*it)->setCumQuantity((*it)->getCumQuantity() + remainQuantity);
            remainQuantity = 0;
        } else {
            removeOrder(*it);
        }
    }
}

uint32_t PriceLevel::getQuantity() const {
    return _quantity;
}
