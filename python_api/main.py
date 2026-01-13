from fastapi import FastAPI
from pydantic import BaseModel
from orderbook_wrapper import add_order, get_book, get_trades
from db import insert_order, insert_trade

app = FastAPI(title="Ultrabook Trading Engine")

class Order(BaseModel):
    order_id: int          # ✅ Added
    instrument_id: int
    side: int   # 0 = BUY, 1 = SELL
    price: float
    qty: int

@app.post("/order")
def place_order(order: Order):
    # ✅ FIXED: Pass all 5 parameters
    add_order(order.order_id, order.instrument_id, order.side, order.price, order.qty)

    # Insert order into DB
    insert_order(order)

    # Fetch trades from orderbook
    trades = get_trades()

    # ✅ FIXED: Use correct trade field names
    for t in trades:
        insert_trade(
            order.instrument_id,  # You'll need to track this differently for trades
            t['buy_order_id'],    
            t['sell_order_id'],
            t['price'],
            t['qty']
        )

    return {"status": "accepted"}

@app.get("/book")
def book():
    return {"orderbook": get_book()}

@app.get("/trades")
def trades():
    return {"trades": get_trades()}