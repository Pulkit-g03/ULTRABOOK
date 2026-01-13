import os
from ctypes import cdll, c_int, c_double, c_char_p

# Add MinGW to PATH so dependencies can be found
mingw_bin = r"C:\msys64\mingw64\bin"
if mingw_bin not in os.environ['PATH']:
    os.environ['PATH'] = mingw_bin + os.pathsep + os.environ['PATH']

lib = cdll.LoadLibrary("E:\\UltraBook\\cpp_engine\\build_x64\\libULTRABOOK.dll")

lib.add_order.argtypes = [c_int, c_int, c_double, c_int]
lib.get_book.restype = c_char_p
lib.get_trades.restype = c_char_p

def add_order(id, side, price, qty):
    lib.add_order(id, side, price, qty)

def get_book():
    return lib.get_book().decode()

def get_trades():
    return lib.get_trades().decode()