#%%
from struct import *

_f = open('t2.bin', 'rb')
buf = _f.read()
_data = unpack('fihBB', buf)

_f.close()

print(_data)

# %%

for v in _data :
    print(v)

# %%
