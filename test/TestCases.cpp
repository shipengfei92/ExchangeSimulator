#define BOOST_TEST_MAIN
#define _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR

#include <map>
#include <boost/test/unit_test.hpp>
#include "../src/utils/Utils.h"
#include "../src/service/ExecutionService.h"
#include "../src/service/QuotationService.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Tests)

    ExecutionService* executor = &ExecutionService::getInstance();
    QuotationService* quotation = &QuotationService::getInstance();
    OrderBookService* orderBookService = &OrderBookService::getInstance();

    void generateAndExecute(const string& order) {
        executor->processOrder(order);
    }
    void executeOrders() {
        orderBookService->clearOrderBooks();
        generateAndExecute("8=FIX.4.2;35=D;11=order001;55=600000;54=2;38=1000;44=10.46;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order002;55=600000;54=2;38=97;44=10.46;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order003;55=600000;54=2;38=653;44=10.45;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order005;55=600000;54=2;38=605;44=10.44;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order006;55=600000;54=2;38=184;44=10.43;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order009;55=600000;54=2;38=428;44=10.42;40=2;59=0");

        generateAndExecute("8=FIX.4.2;35=D;11=order004;55=600000;54=1;38=3000;44=10.41;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order007;55=600000;54=1;38=800;44=10.41;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order0013;55=600000;54=1;38=65;44=10.41;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order008;55=600000;54=1;38=13201;44=10.40;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order010;55=600000;54=1;38=1738;44=10.39;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order011;55=600000;54=1;38=3264;44=10.38;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order012;55=600000;54=1;38=1001;44=10.37;40=2;59=0");

    }

    BOOST_AUTO_TEST_CASE(NoExecutionTest) {
        executeOrders();
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(LimitGTCOrderTest1) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order101;55=600000;54=1;38=3500;44=10.44;40=2;59=0");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(LimitGTCOrderTest2) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order102;55=600000;54=2;38=3500;44=10.40;40=2;59=0");
        quotation->printQuotations();
    }


    BOOST_AUTO_TEST_CASE(LimitIOCOrderTest1) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order103;55=600000;54=1;38=3500;44=10.44;40=2;59=3");
        quotation->printQuotations();
        generateAndExecute("8=FIX.4.2;35=D;11=order104;55=600000;54=1;38=3500;44=10.42;40=2;59=3");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(LimitFOKOrderTest1) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order105;55=600000;54=2;38=3500;44=10.40;40=2;59=4");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(LimitFOKOrderTest2) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order106;55=600000;54=2;38=20000;44=10.40;40=2;59=4");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(MarketOrderTest1) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order107;55=600000;54=1;38=2000;40=1;59=0");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(MarketOrderTest2) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order108;55=600000;54=1;38=4000;40=1;59=0");
        quotation->printQuotations();
    }

    BOOST_AUTO_TEST_CASE(MultiSymbolTest) {
        executeOrders();
        generateAndExecute("8=FIX.4.2;35=D;11=order109;55=600001;54=2;38=97;44=10.5;40=2;59=0");
        generateAndExecute("8=FIX.4.2;35=D;11=order110;55=600001;54=1;38=97;44=10.4;40=2;59=0");
        quotation->printQuotations();
    }

BOOST_AUTO_TEST_SUITE_END()

