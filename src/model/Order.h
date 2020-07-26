#pragma once

#include <string>
#include <ostream>
#include "../utils/Constants.h"

using namespace std;

class Order {
private:
    string _orderId;
    char _msgType;
    string _symbol;
    uint32_t _side;
    uint32_t _price;
    uint32_t _quantity;
    uint32_t _cumQuantity;
    OrderType _orderType;
    TimeInForce _tif;

public:
    Order() {}

    Order(const string &orderId, const string &symbol, uint32_t side, uint32_t price, uint32_t quantity,
          OrderType orderType, TimeInForce tif);

    bool operator==(const Order&);

    char getMsgType() const;

    void setMsgType(char msgType);

    void setPrice(uint32_t price);

    void setOrderId(const string &orderId);

    const string &getOrderId() const;

    const string &getSymbol() const;

    void setSymbol(const string &symbol);

    uint32_t getSide() const;

    void setSide(uint32_t side);

    uint32_t getPrice() const;

    uint32_t getQuantity() const;

    void setQuantity(uint32_t quantity);

    uint32_t getCumQuantity() const;

    void setCumQuantity(uint32_t cumQuantity);

    OrderType getOrderType() const;

    void setOrderType(OrderType orderType);

    TimeInForce getTif() const;

    void setTif(TimeInForce tif);

};