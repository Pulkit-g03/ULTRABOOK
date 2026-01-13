#include "../include/orderbook.h"

static OrderBook* book = nullptr;

extern "C" {

__declspec(dllexport) void init_book() {
    if (!book)
        book = new OrderBook();
}

// Fixed: added instrument_id as second argument
__declspec(dllexport) void add_order(int id, int instrument_id, int side, double price, int qty) {
    if (!book) init_book();

    Order o(
        id,
        instrument_id,               // ✅ instrument id
        static_cast<Side>(side),     // convert int to enum Side
        price,
        qty
    );

    book->addOrder(o);
}

__declspec(dllexport) const char* get_book() {
    static std::string snapshot;
    if (!book) init_book();
    snapshot = book->getBookSnapshot();
    return snapshot.c_str();
}

__declspec(dllexport) const char* get_trades() {
    static std::string t;
    if (!book) init_book();
    t = book->getTrades();
    return t.c_str();
}

}
