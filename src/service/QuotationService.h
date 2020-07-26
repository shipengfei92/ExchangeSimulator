#pragma once

#include "OrderBookService.h"
#include <string>
#include <iostream>

using namespace std;

class QuotationService {
private:
    OrderBookService* _orderBookService;

    QuotationService () {
        _orderBookService = &OrderBookService::getInstance();
    }
    QuotationService(const QuotationService&) = delete;
    QuotationService(QuotationService&& ) = delete;
    QuotationService operator=(const QuotationService&) = delete;
public:
    static QuotationService& getInstance() {
        static QuotationService quotesService;
        return quotesService;
    }

    void printQuotations();
    void printQuotations(const string& symbol);
    uint32_t getBestBid(const string& symbol);
    uint32_t getBestAsk(const string& symbol);

};