from fastapi import FastAPI
from pydantic import BaseModel
from orderbook_wrapper import add_order, get_book, get_trades
from db import insert_order, insert_trade
import json

app = FastAPI(title="Ultrabook Trading Engine")

class Order(BaseModel):
    id: int
    side: int   # 0 = BUY, 1 = SELL
    price: float
    qty: int

@app.post("/order")
def place_order(order: Order):
    add_order(order.id, order.side, order.price, order.qty)
    insert_order(order)
    # Fetch and insert new trades (assuming get_trades returns all; in production, track deltas)
    trades_json = get_trades()
    trades = json.loads(trades_json) if trades_json else []
    # Insert only new trades; for simplicity, insert all (or implement last_known_trade logic)
    for t in trades:
        insert_trade(t['buy'], t['sell'], t['price'], t['qty'])
    return {"status": "accepted"}

@app.get("/book")
def book():
    return {"orderbook": get_book()}

@app.get("/trades")
def trades():
    return {"trades": get_trades()}