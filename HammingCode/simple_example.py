import numpy as np
from functools import reduce
import operator as op

# generator random data

bits = np.random.randint(0, 2, 16)
print(bits)

# Implement 1 (python style):

# op.xor === lambda x,y:x^y
err_pos = reduce(op.xor, [i for i, bit in enumerate(bits) if bit])
print(err_pos)

# Implement 2 (c style):

err_pos = 0
for i in range(16):
    if bits[i]:
        err_pos ^= i
print(err_pos)

# fixed

# a ^= 1 === a = not a
bits[err_pos] ^= 1
print(bits)

# check again
err_pos = reduce(op.xor, [i for i, bit in enumerate(bits) if bit])
print(err_pos)
