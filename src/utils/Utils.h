#pragma once

#include <string>
#include "../model/Order.h"

using namespace std;

namespace Utils {

    // 8=FIX.4.2;35=A;
    static Order* orderParser(string& order){
        return new Order();
    };
}