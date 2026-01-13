import sqlite3

conn = sqlite3.connect("ultrabook.db", check_same_thread=False)
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS orders (
    id INTEGER PRIMARY KEY,
    side INTEGER,
    price REAL,
    quantity INTEGER,
    timestamp TEXT
)
""")

cursor.execute("""
CREATE TABLE IF NOT EXISTS trades (
    trade_id INTEGER PRIMARY KEY AUTOINCREMENT,
    buy_id INTEGER,
    sell_id INTEGER,
    price REAL,
    quantity INTEGER,
    timestamp TEXT
)
""")

conn.commit()

def insert_order(order):
    cursor.execute(
        "INSERT INTO orders VALUES (?, ?, ?, ?, datetime('now'))",
        (order.id, order.side, order.price, order.qty)
    )
    conn.commit()

def insert_trade(buy_id, sell_id, price, qty):
    cursor.execute(
        """
        INSERT INTO trades (buy_id, sell_id, price, quantity, timestamp)
        VALUES (?, ?, ?, ?, datetime('now'))
        """,
        (buy_id, sell_id, price, qty)
    )
    conn.commit()
