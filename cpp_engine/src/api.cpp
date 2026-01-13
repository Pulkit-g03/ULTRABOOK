#include "../include/orderbook.h"

static OrderBook ob;

extern "C" {

void add_order(int id, int side, double price, int qty) {
    ob.addOrder(Order(id, static_cast<Side>(side), price, qty));
}

const char* get_book() {
    static std::string snapshot;
    snapshot = ob.getBookSnapshot();
    return snapshot.c_str();
}

const char* get_trades() {
    static std::string trade_snapshot;
    trade_snapshot = ob.getTrades();
    return trade_snapshot.c_str();
}

}
