from fastapi import FastAPI
from pydantic import BaseModel
from orderbook_wrapper import add_order, get_book, get_trades
from db import insert_order, insert_trade

app = FastAPI(title="Ultrabook Trading Engine")

class Order(BaseModel):
    instrument_id: int
    side: int   # 0 = BUY, 1 = SELL
    price: float
    qty: int

@app.post("/order")
def place_order(order: Order):
    # Add order to in-memory orderbook
    add_order(order.instrument_id, order.side, order.price, order.qty)

    # Insert order into DB
    insert_order(order)

    # Fetch trades from orderbook (already a Python list now)
    trades = get_trades()

    # Insert trades into DB
    for t in trades:
        insert_trade(
            t['instrument_id'],
            t['buy_order_id'],   # assuming your trade dict uses these keys
            t['sell_order_id'],
            t['price'],
            t['qty']
        )

    return {"status": "accepted"}

@app.get("/book")
def book():
    return {"orderbook": get_book()}  # already a dict

@app.get("/trades")
def trades():
    return {"trades": get_trades()}   # already a list
