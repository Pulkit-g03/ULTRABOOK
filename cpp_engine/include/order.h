#pragma once
#include <chrono>

enum Side { BUY = 0, SELL = 1 };

struct Order {
    int id;
    Side side;
    double price;
    int quantity;
    std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

    Order(int i, Side s, double p, int q)
        : id(i), side(s), price(p), quantity(q),
          timestamp(std::chrono::high_resolution_clock::now()) {}
};
