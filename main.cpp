#include <iostream>
#include "src/utils/Utils.h"
#include "src/service/ExecutionService.h"
#include "src/service/QuotationService.h"

using namespace std;

int main() {

    ExecutionService* executor = &ExecutionService::getInstance();
    QuotationService* quotation = &QuotationService::getInstance();
    string newLimitOrder = "8=FIX.4.2;35=D;11=order001;55=600000;54=1;38=100;44=10.12;40=2;59=0";
    string newLimitFOKOrder = "8=FIX.4.2;35=D;11=order004;55=600000;54=1;38=200;44=10.13;40=2;59=3";
    string newLimitIOCOrder = "8=FIX.4.2;35=D;11=order004;55=600000;54=1;38=300;44=10.14;40=2;59=4";
    string cancelLimitOrder = "8=FIX.4.2;35=F;11=order002;55=600000;54=1";
    string newMarketOrder = "8=FIX.4.2;35=D;11=order003;55=600000;54=1;38=100;40=1;59=0";
    string str;
    cout << "Please input order in FIX format ('exit' for exit loop):" << endl;
    while (getline(cin, str)) {
        if (str == "exit") break;
        executor->processOrder(str);
        quotation->printQuotations();
    }
    return 0;
}
