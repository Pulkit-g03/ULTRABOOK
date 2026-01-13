#include "../include/orderbook.h"
#include <sstream>

void OrderBook::addOrder(Order order) {
    if (order.side == BUY) {
        matchBuy(order);
        if (order.quantity > 0)
            buyOrders[order.price].push_back(order);
    } else {
        matchSell(order);
        if (order.quantity > 0)
            sellOrders[order.price].push_back(order);
    }
}

void OrderBook::matchBuy(Order& buy) {
    while (!sellOrders.empty() && buy.quantity > 0) {
        auto it = sellOrders.begin();
        if (buy.price < it->first) break;

        auto& queue = it->second;
        while (!queue.empty() && buy.quantity > 0) {
            Order& sell = queue.front();
            int qty = std::min(buy.quantity, sell.quantity);

            trades.push_back({buy.id, sell.id, it->first, qty});

            buy.quantity -= qty;
            sell.quantity -= qty;

            if (sell.quantity == 0)
                queue.pop_front();
        }
        if (queue.empty())
            sellOrders.erase(it);
    }
}

void OrderBook::matchSell(Order& sell) {
    while (!buyOrders.empty() && sell.quantity > 0) {
        auto it = buyOrders.begin();
        if (sell.price > it->first) break;

        auto& queue = it->second;
        while (!queue.empty() && sell.quantity > 0) {
            Order& buy = queue.front();
            int qty = std::min(sell.quantity, buy.quantity);

            trades.push_back({buy.id, sell.id, it->first, qty});

            sell.quantity -= qty;
            buy.quantity -= qty;

            if (buy.quantity == 0)
                queue.pop_front();
        }
        if (queue.empty())
            buyOrders.erase(it);
    }
}

std::string OrderBook::getBookSnapshot() const {
    std::ostringstream oss;
    oss << "{ \"buy\": [";
    for (const auto& p : buyOrders)
        oss << "{ \"price\": " << p.first << ", \"orders\": " << p.second.size() << " },";
    oss << "], \"sell\": [";
    for (const auto& p : sellOrders)
        oss << "{ \"price\": " << p.first << ", \"orders\": " << p.second.size() << " },";
    oss << "] }";
    return oss.str();
}

std::string OrderBook::getTrades() const {
    std::ostringstream oss;
    oss << "[";
    for (const auto& t : trades)
        oss << "{ \"buy\": " << t.buy_id
            << ", \"sell\": " << t.sell_id
            << ", \"price\": " << t.price
            << ", \"qty\": " << t.quantity << " },";
    oss << "]";
    return oss.str();
}
