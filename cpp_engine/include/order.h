#pragma once
#include <chrono>

enum Side { BUY = 0, SELL = 1 };

struct Order {
    int id;
    int instrument_id;   // new field
    Side side;
    double price;
    int quantity;
    std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

    Order(int i, int instr, Side s, double p, int q)
        : id(i), instrument_id(instr), side(s), price(p), quantity(q),
          timestamp(std::chrono::high_resolution_clock::now()) {}
};

