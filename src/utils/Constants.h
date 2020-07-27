#pragma once

#include <string>
#include <map>
#include <boost/assign/list_of.hpp>
using namespace std;

// Side
static constexpr uint32_t BUY = 1;
static constexpr uint32_t SELL = 2;

// MsgType
static constexpr char New = 'D';
static constexpr char Cancel = 'F';

// Price multiplier
static constexpr uint32_t MULTIPLIER = 100;

// FIX tag
static constexpr uint32_t FixVersion = 8;
static constexpr uint32_t OrderId = 11;
static constexpr uint32_t MsgType = 35;
static constexpr uint32_t Symbol = 55;
static constexpr uint32_t Price = 44;
static constexpr uint32_t Quantity = 38;
static constexpr uint32_t Side = 54;
static constexpr uint32_t OrderTypeTag = 40;
static constexpr uint32_t TimeInForceTag = 59;

enum class TimeInForce : uint8_t
{
    GTC = 0, // good till cancel
    IOC = 3, // immediate or cancel
    FOK = 4, // fill or kill
};

static map<string, TimeInForce> TimeInForceMap = boost::assign::map_list_of
        ("0",TimeInForce::GTC)
        ("3",TimeInForce::IOC)
        ("4",TimeInForce::FOK);

enum class OrderType : uint8_t
{
    Market = 1,
    Limit = 2,
};

static map<string, OrderType> OrderTypeMap = boost::assign::map_list_of
        ("1",OrderType::Market)
        ("2",OrderType::Limit);