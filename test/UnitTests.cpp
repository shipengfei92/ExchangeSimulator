#define BOOST_TEST_MAIN
#define _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../src/utils/Utils.h"
#include "../src/utils/Constants.h"
#include "../src/model/Order.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(UtilTests)

BOOST_AUTO_TEST_CASE(DateTest) {
        BOOST_CHECK_EQUAL(365, 365);
    }

BOOST_AUTO_TEST_CASE(OrderTest) {
    Order* order1 = new Order();
    Order* order2 = new Order();
    cout << order1->getSeqNo() << endl;
    cout << order2->getSeqNo() << endl;
}

BOOST_AUTO_TEST_SUITE_END()

