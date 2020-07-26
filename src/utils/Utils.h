#pragma once

#include <string>
#include <iostream>
#include "../model/Order.h"
#include "Constants.h"

#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

#define likely(x) __builtin_expect(!!(x), 1)

namespace Utils {

    template<typename T>
    static void printVector(T& v) {
        for(auto &vv: v) {
            cout << vv << "\t";
        }
        cout << endl;
    }

    static Order* orderParser(const string& orderStr){
        vector<string> split_string;
        boost::split(split_string, orderStr, boost::is_any_of("=|;"));
        printVector(split_string);
        Order* order = new Order();
        try {
            for (uint32_t i = 0; i< split_string.size(); i = i + 2) {
                uint32_t fixTag = stoi(split_string[i]);
                string value = split_string[i+1];
                switch (fixTag) {
                    case 8:
                        break;
                    case 11:
                        order->setOrderId(value);
                        break;
                    case 35:
                        if(likely(value[0] == New)) {
                            order->setMsgType(New);
                        } else {
                            order->setMsgType(Cancel);
                        }
                        break;
                    case 44:
                        order->setPrice(round(stod(value) * MULTIPLIER));
                        break;
                    case 55:
                        order->setSymbol(value);
                        break;
                    case 38:
                        order->setQuantity(stoi(value));
                        break;
                    case 54:
                        order->setSide(stoi(value));
                        break;
                    case 40:
                        order->setOrderType(OrderTypeMap[value]);
                        break;
                    case 59:
                        order->setTif(TimeInForceMap[value]);
                        break;
                    default:
                        BOOST_LOG_TRIVIAL(error) << "unsupported tag found." << endl;
                }
            }
        } catch (exception& e) {
            BOOST_LOG_TRIVIAL(error) << "failed to parser order." << endl;
            order = nullptr;
        }
        return order;
    };

}