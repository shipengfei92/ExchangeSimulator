#include "Order.h"

Order::Order(const string &orderId, const string &symbol, uint32_t side, uint32_t price, uint32_t quantity,
             OrderType orderType, TimeInForce tif) :
                                                                           _orderId(orderId),
                                                                           _symbol(symbol),
                                                                           _side(side),
                                                                           _price(price),
                                                                           _quantity(quantity),
                                                                           _orderType(orderType),
                                                                           _tif(tif) {}

bool Order::operator==(const Order &r) {
    return r._orderId == this->_orderId;
}

const string &Order::getOrderId() const {
    return _orderId;
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

uint32_t Order::getPrice() const {
    return _price;
}

uint32_t Order::getQuantity() const {
    return _quantity;
}

void Order::setQuantity(uint32_t quantity) {
    _quantity = quantity;
}

uint32_t Order::getCumQuantity() const {
    return _cumQuantity;
}

void Order::setCumQuantity(uint32_t cumQuantity) {
    _cumQuantity = cumQuantity;
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

char Order::getMsgType() const {
    return _msgType;
}

void Order::setMsgType(char msgType) {
    _msgType = msgType;
}

void Order::setPrice(uint32_t price) {
    _price = price;
}

void Order::setOrderId(const string &orderId) {
    _orderId = orderId;
}
