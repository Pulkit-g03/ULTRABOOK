#pragma once
#include "order.h"
#include "trade.h"
#include <map>
#include <deque>
#include <vector>
#include <string>

class OrderBook {
private:
    std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
    std::map<double, std::deque<Order>> sellOrders;
    std::vector<Trade> trades;

    void matchBuy(Order& order);
    void matchSell(Order& order);

public:
    void addOrder(Order order);
    std::string getBookSnapshot() const;
    std::string getTrades() const;
};
