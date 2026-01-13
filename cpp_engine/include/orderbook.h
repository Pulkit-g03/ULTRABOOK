#pragma once
#include "order.h"
#include "trade.h"
#include <map>
#include <deque>
#include <vector>
#include <string>

class OrderBook {
private:
    struct Book {
        std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
        std::map<double, std::deque<Order>> sellOrders;
    };

    std::map<int, Book> instrumentBooks;   // instrument_id -> Book
    std::vector<Trade> trades;

    void matchBuy(int instrument_id, Order& order);
    void matchSell(int instrument_id, Order& order);

public:
    void addOrder(Order order);
    std::string getBookSnapshot() const;
    std::string getTrades() const;
};
