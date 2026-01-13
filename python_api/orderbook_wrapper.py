import os
from ctypes import cdll, c_int, c_double, c_char_p
import json
import re

# Add MinGW to PATH so dependencies can be found
mingw_bin = r"C:\\msys64\\mingw64\\bin"
if mingw_bin not in os.environ['PATH']:
    os.environ['PATH'] = mingw_bin + os.pathsep + os.environ['PATH']

lib = cdll.LoadLibrary("E:\\UltraBook\\cpp_engine\\build_x64\\libULTRABOOK.dll")

# ✅ FIXED: Added instrument_id parameter
lib.add_order.argtypes = [c_int, c_int, c_int, c_double, c_int]
#                         order_id, instrument_id, side, price, qty
lib.get_book.restype = c_char_p
lib.get_trades.restype = c_char_p

# ✅ FIXED: Added order_id and instrument_id parameters
def add_order(order_id, instrument_id, side, price, qty):
    lib.add_order(order_id, instrument_id, side, price, qty)

def parse_json_string(s: str):
    """
    Fix common DLL JSON formatting issues:
    - Remove trailing commas
    - Convert to Python object
    """
    if not s:
        return {}
    # Remove trailing commas before } or ]
    s = re.sub(r',\s*([}\]])', r'\1', s)
    try:
        return json.loads(s)
    except json.JSONDecodeError:
        return {}  # fallback

def get_book():
    raw = lib.get_book().decode()
    return parse_json_string(raw)

def get_trades():
    raw = lib.get_trades().decode()
    return parse_json_string(raw)