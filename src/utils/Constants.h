#pragma once

#include <cstdint>

enum class FixTags: uint8_t
{
    MsgType = 35,
    OrderType = 40,
    Price = 44,
    Quantity = 38,
    Side = 54,
    TimeInForce = 59,
    ExecType = 150,
};

enum class TimeInForce : uint8_t
{
    GTC = 0, // good till cancel
    IOC = 3, // immediate or cancel
    FOK = 4, // fill or kill
};

enum class OrderType : uint8_t
{
    Market = 1,
    Limit = 2,
};
