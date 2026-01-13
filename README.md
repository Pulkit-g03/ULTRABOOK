ULTRABOOK – Low Latency Order Book & Matching Engine

ULTRABOOK is a C++-based limit order book and matching engine, exposed via a FastAPI backend and a React frontend.
The project is designed to reflect real-world trading system architecture, focusing on correctness, extensibility, and low-latency design principles.

Key Features
*   C++ Matching Engine
    *   Price–time priority order matching
    *   Separate BUY and SELL books
    *   Partial and full order fills
    *   STL-based data structures (map, deque, vector)

*   C API Interface
    *   Shared library (.dll) exported using extern "C"
    *   Python integration via ctypes

*   FastAPI Backend
    *   REST APIs for placing orders
    *   Snapshot of order book and trade history

*   SQLite Persistence
    *   Orders and trades stored persistently
    *   Supports multiple instruments

*   React Frontend
    *   Place BUY/SELL orders
    *   Live order book view
    *   Trade history visualization

How to Run:

Step 1: Build C++ engine 

cd cpp_engine
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

Step 2: Run Backend

cd python_api
uvicorn main:app --reload

Step 3: Run Frontend

cd frontend
npm install
npm run dev
