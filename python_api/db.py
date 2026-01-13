import sqlite3

conn = sqlite3.connect("ultrabook.db", check_same_thread=False)
cursor = conn.cursor()

# ORDERS TABLE
cursor.execute("""
CREATE TABLE IF NOT EXISTS orders (
    order_id INTEGER PRIMARY KEY AUTOINCREMENT,
    instrument_id INTEGER,
    side INTEGER,
    price REAL,
    quantity INTEGER,
    timestamp TEXT
)
""")

# TRADES TABLE
cursor.execute("""
CREATE TABLE IF NOT EXISTS trades (
    trade_id INTEGER PRIMARY KEY AUTOINCREMENT,
    instrument_id INTEGER,
    buy_order_id INTEGER,
    sell_order_id INTEGER,
    price REAL,
    quantity INTEGER,
    timestamp TEXT
)
""")

conn.commit()

def insert_order(order):
    cursor.execute(
        """
        INSERT INTO orders (instrument_id, side, price, quantity, timestamp)
        VALUES (?, ?, ?, ?, datetime('now'))
        """,
        (order.instrument_id, order.side, order.price, order.qty)
    )
    conn.commit()

def insert_trade(instrument_id, buy_order_id, sell_order_id, price, qty):
    cursor.execute(
        """
        INSERT INTO trades
        (instrument_id, buy_order_id, sell_order_id, price, quantity, timestamp)
        VALUES (?, ?, ?, ?, ?, datetime('now'))
        """,
        (instrument_id, buy_order_id, sell_order_id, price, qty)
    )
    conn.commit()
