#include "Order.h"

uint32_t Order::getOrderId() const {
    return _orderId;
}

void Order::setOrderId(uint32_t orderId) {
    _orderId = orderId;
}

const string &Order::getSymbol() const {
    return _symbol;
}

void Order::setSymbol(const string &symbol) {
    _symbol = symbol;
}

uint32_t Order::getSide() const {
    return _side;
}

void Order::setSide(uint32_t side) {
    _side = side;
}

int32_t Order::getPrice() const {
    return _price;
}

void Order::setPrice(int32_t price) {
    _price = price;
}

uint32_t Order::getVolume() const {
    return _volume;
}

void Order::setVolume(uint32_t volume) {
    _volume = volume;
}

OrderType Order::getOrderType() const {
    return _orderType;
}

void Order::setOrderType(OrderType orderType) {
    _orderType = orderType;
}

TimeInForce Order::getTif() const {
    return _tif;
}

void Order::setTif(TimeInForce tif) {
    _tif = tif;
}

Order::Order(uint32_t orderId, const string &symbol, uint32_t side, int32_t price, uint32_t volume, OrderType orderType,
             TimeInForce tif) : _orderId(orderId), _symbol(symbol), _side(side), _price(price), _volume(volume),
                                _orderType(orderType), _tif(tif) {}

