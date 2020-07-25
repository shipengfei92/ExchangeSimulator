#include "PriceLevel.h"

PriceLevel::PriceLevel(uint32_t side_, uint32_t price_, OrderBook &orderBook_) : _side(side_), _price(price_),
                                                                                          _orderBook(orderBook_) {}
