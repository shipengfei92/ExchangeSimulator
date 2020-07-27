#include "QuotationService.h"

void QuotationService::printQuotations() {
    auto orderBookMap = _orderBookService->getAllOrderBook();
    for (auto orderBook: orderBookMap) {
        printQuotations(orderBook.first);
    }
}

void QuotationService::printQuotations(const string &symbol) {
    auto orderBook = _orderBookService->getOrderBook(symbol);
    auto& sell = orderBook->getSellPriceLevels();
    auto it = sell.rbegin();
    uint32_t n = 1;
    cout << "OrderBook for symbol: " << symbol << endl;
    cout << "=============SELL=============="<< endl;
    while(it != sell.rend() && n <= 5) {
        cout << "Sell " << n << "\t Price: " << it->first * 1.0 / MULTIPLIER
        << "\t Quantity: " << it->second->getQuantity() << endl;
        ++it;
        ++n;
    }

    n = 1;
    auto& buy = orderBook->getBuyPriceLevels();
    auto it2 = buy.rbegin();
    cout << "=============BUY=============="<< endl;
    while(it2 != buy.rend() && n <= 5) {
        cout << "Buy " << n << "\t Price: " << it2->first * 1.0 / MULTIPLIER
        << "\t Quantity: " << it2->second->getQuantity() << endl;
        ++it2;
        ++n;
    }

}
