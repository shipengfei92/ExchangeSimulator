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
        _orderList.erase(it);
        _quantity -= ((*it)->getQuantity() - (*it)->getCumQuantity());
    }
}

void PriceLevel::executeOrder(Order *order) {
    auto cumQuantity = order->getCumQuantity();
    auto remainQuantity = order->getQuantity() - cumQuantity;
    auto it = _orderList.begin();
    while(remainQuantity > 0 && it!= _orderList.end()) {
        auto quantity = (*it)->getQuantity() - (*it)->getCumQuantity();
        if (quantity > remainQuantity) {
            (*it)->setCumQuantity((*it)->getCumQuantity() + remainQuantity);
            cumQuantity += remainQuantity;
            _quantity -= remainQuantity;
            remainQuantity = 0;
        } else {
            _orderList.erase(it);
            _quantity -= quantity;
            cumQuantity += quantity;
            remainQuantity -= quantity;
            ++it;
        }
    }
    order->setCumQuantity(cumQuantity);
}

uint32_t PriceLevel::getQuantity() const {
    return _quantity;
}
