#pragma once

#include <string>
#include "../utils/Constants.h"

using namespace std;

class Order {
private:
    uint32_t _orderId;
    string _symbol;
    uint32_t _side;
    int32_t _price;
    uint32_t _volume;
    OrderType _orderType;
    TimeInForce _tif;

public:

    Order () {};

    Order(uint32_t orderId, const string &symbol, uint32_t side, int32_t price, uint32_t volume, OrderType orderType,
          TimeInForce tif);

    uint32_t getOrderId() const;

    void setOrderId(uint32_t orderId);

    const string &getSymbol() const;

    void setSymbol(const string &symbol);

    uint32_t getSide() const;

    void setSide(uint32_t side);

    int32_t getPrice() const;

    void setPrice(int32_t price);

    uint32_t getVolume() const;

    void setVolume(uint32_t volume);

    OrderType getOrderType() const;

    void setOrderType(OrderType orderType);

    TimeInForce getTif() const;

    void setTif(TimeInForce tif);

};