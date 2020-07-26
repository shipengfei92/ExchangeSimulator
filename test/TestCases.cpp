#define BOOST_TEST_MAIN
#define _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../src/utils/Utils.h"
#include "../src/utils/Constants.h"
#include "../src/model/Order.h"
#include "../src/service/ExecutionService.h"
#include "../src/service/QuotationService.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Tests)

    string newLimitOrder0 = "8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.12;40=2;59=0";
    string newLimitOrder1 = "8=FIX.4.2;35=D;11=order002;55=600000;54=1;38=100;44=10.13;40=2;59=0";
    string newLimitOrder2 = "8=FIX.4.2;35=D;11=order003;55=600000;54=1;38=100;44=10.14;40=2;59=0";
    string newLimitOrder3 = "8=FIX.4.2;35=D;11=order004;55=600000;54=1;38=100;44=10.15;40=2;59=0";
    ExecutionService* executor = &ExecutionService::getInstance();
    QuotationService* quotation = &QuotationService::getInstance();
    void generateAndExecute(const string& order) {
        executor->processOrder(order);
    }
    void executeOrders() {
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.16;40=2;59=0");

        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=100;44=10.16;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=100;44=10.16;40=2;59=0");

    }


BOOST_AUTO_TEST_CASE(DateTest) {
    executeOrders();
}

BOOST_AUTO_TEST_CASE(OrderTest) {

    executor->processOrder(newLimitOrder0);
    executor->processOrder(newLimitOrder1);
    executor->processOrder(newLimitOrder2);
    executor->processOrder(newLimitOrder3);

    quotation->printQuotations();
}

BOOST_AUTO_TEST_SUITE_END()

