import { useEffect, useState } from "react";

export default function App() {
  const [order, setOrder] = useState({ 
    order_id: "", 
    instrument_id: "",  // ✅ Added
    side: 0, 
    price: "", 
    qty: "" 
  });
  const [book, setBook] = useState("");
  const [trades, setTrades] = useState("");

  const API = "http://127.0.0.1:8000";

  const fetchBook = async () => {
    const res = await fetch(`${API}/book`);
    setBook(await res.text());
  };

  const fetchTrades = async () => {
    const res = await fetch(`${API}/trades`);
    setTrades(await res.text());
  };

  const submitOrder = async () => {
    await fetch(`${API}/order`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        order_id: Number(order.order_id),           // ✅ Fixed name
        instrument_id: Number(order.instrument_id), // ✅ Added
        side: Number(order.side),
        price: Number(order.price),
        qty: Number(order.qty)
      })
    });

    fetchBook();
    fetchTrades();
  };

  useEffect(() => {
    fetchBook();
    fetchTrades();
  }, []);

  return (
    <div className="app-container">
      <h1>ULTRABOOK Matching Engine</h1>

      <div className="grid">
        {/* ORDER BOOK */}
        <div className="card-box">
          <h2>Order Book</h2>
          <pre className="pre-box">{book}</pre>
        </div>

        {/* PLACE ORDER */}
        <div className="card-box">
          <h2>Place Order</h2>

          <input
            className="input"
            placeholder="Order ID"
            onChange={(e) => setOrder({ ...order, order_id: e.target.value })} // ✅ Fixed
          />

          {/* ✅ ADDED: Instrument ID input */}
          <input
            className="input"
            placeholder="Instrument ID (e.g., 1 for AAPL, 2 for GOOGL)"
            onChange={(e) => setOrder({ ...order, instrument_id: e.target.value })}
          />

          <select
            className="input"
            onChange={(e) => setOrder({ ...order, side: e.target.value })}
          >
            <option value={0}>Buy</option>
            <option value={1}>Sell</option>
          </select>

          <input
            className="input"
            placeholder="Price"
            onChange={(e) => setOrder({ ...order, price: e.target.value })}
          />

          <input
            className="input"
            placeholder="Quantity"
            onChange={(e) => setOrder({ ...order, qty: e.target.value })}
          />

          <button className="button" onClick={submitOrder}>
            Submit Order
          </button>
        </div>
      </div>

      {/* TRADES */}
      <div className="card-box trades">
        <h2>Trade History</h2>
        <pre className="pre-box">{trades}</pre>
      </div>
    </div>
  );
}