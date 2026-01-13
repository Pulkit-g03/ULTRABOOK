cmake_minimum_required(VERSION 3.10)
project(ULTRABOOK)

set(CMAKE_CXX_STANDARD 17)

add_library(ULTRABOOK SHARED
    src/orderbook.cpp
    src/api.cpp
)

target_include_directories(ULTRABOOK PUBLIC include)
