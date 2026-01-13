#include "../include/orderbook.h"
#include <sstream>

void OrderBook::addOrder(Order order) {
    Book& book = instrumentBooks[order.instrument_id];

    if (order.side == BUY) {
        matchBuy(order.instrument_id, order);
        if (order.quantity > 0)
            book.buyOrders[order.price].push_back(order);
    } else {
        matchSell(order.instrument_id, order);
        if (order.quantity > 0)
            book.sellOrders[order.price].push_back(order);
    }
}


void OrderBook::matchBuy(int instrument_id, Order& buy) {
    Book& book = instrumentBooks[instrument_id];
    while (!book.sellOrders.empty() && buy.quantity > 0) {
        auto it = book.sellOrders.begin();
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
            book.sellOrders.erase(it);
    }
}

void OrderBook::matchSell(int instrument_id, Order& sell) {
    Book& book = instrumentBooks[instrument_id];
    while (!book.buyOrders.empty() && sell.quantity > 0) {
        auto it = book.buyOrders.begin();
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
            book.buyOrders.erase(it);
    }
}



std::string OrderBook::getBookSnapshot() const {
    std::ostringstream oss;
    oss << "{";
    for (auto it = instrumentBooks.begin(); it != instrumentBooks.end(); ++it) {
        int instr_id = it->first;
        const Book& book = it->second;

        if (it != instrumentBooks.begin()) oss << ",";

        oss << "\"" << instr_id << "\": { \"buy\": [";
        for (const auto& p : book.buyOrders)
            oss << "{ \"price\": " << p.first << ", \"orders\": " << p.second.size() << " },";
        oss << "], \"sell\": [";
        for (const auto& p : book.sellOrders)
            oss << "{ \"price\": " << p.first << ", \"orders\": " << p.second.size() << " },";
        oss << "] }";
    }
    oss << "}";
    return oss.str();
}


std::string OrderBook::getTrades() const {
    std::ostringstream oss;
    oss << "[";
    for (const auto& t : trades)
        oss << "{ \"buy_order_id\": " << t.buy_id
            << ", \"sell_order_id\": " << t.sell_id
            << ", \"price\": " << t.price
            << ", \"qty\": " << t.quantity << " },";
    oss << "]";
    return oss.str();
}
