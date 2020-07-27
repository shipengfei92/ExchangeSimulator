#include <iostream>
#include "src/utils/Utils.h"
#include "src/service/ExecutionService.h"
#include "src/service/QuotationService.h"

using namespace std;

int main() {

    ExecutionService* executor = &ExecutionService::getInstance();
    QuotationService* quotation = &QuotationService::getInstance();
    string str;
    cout << "Please input order in FIX format ('exit' for exit loop):" << endl;
    while (getline(cin, str)) {
        if (str == "exit") break;
        executor->processOrder(str);
        quotation->printQuotations();
    }
    return 0;
}
