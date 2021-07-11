import numpy as np
from functools import reduce
import operator as op
import sys

def hamming_status(x):
    sta = 0
    i = 0
    while x:
        if x & 1:
            sta ^= i
        x >>= 1
        i += 1
    return sta


def hamming_encode16(x):
    
    hc = 0
    l = 2 # l >= 3
    for i in range(11):
        if l & l+1 :
            l += 1
        else:
            l += 2
        hc |= (x & 1) << l
        x >>= 1

    sta = hamming_status(hc)
    for l in range(0, 4):
        if sta & 1:
            # hc |= 2**2**l
            hc |= 1 << (1 << l)
        sta >>= 1
    sta = hamming_status(hc)

    return hc


def hamming_encode(x):

    hc = bytes(0)

    while x:
        hc += hamming_encode16(x & 0x7ff).to_bytes(2, 'little')
        x >>= 11
    
    return hc


def hamming_decode16(x):
    
    i = 2 # i >= 3
    l = 0
    c = 0

    x >>= 3

    for i in range(3, 16):

        if not i & (i-1):
            x >>= 1
            continue

        if x & 1:
            c |= 1 << l
        
        l += 1
        x >>= 1

    return c

def hamming_decode(x):
    
    l = 0
    c = 0
    x = [int.from_bytes(x[i:i+2], 'little') for i in range(0, len(x), 2)]
    for m in x:
        # check
        sta = hamming_status(m)
        print('check:', sta)
        # fix
        m ^= 1 << sta
        # decode
        c |= hamming_decode16(m) << l
        l += 11
    
    return c


if __name__ == "__main__":

    # input

    i = 1145141919810
    if len(sys.argv) == 2:
        i = int(sys.argv[1])
    print('input:')
    print(i)
    print()

    # encode

    hc = hamming_encode(i)
    print('hamming encode(hex little):')
    print(hc.hex())
    print()

    # noise

    hc_noise = bytes([hc[0] ^ 0x40]) + hc[1:]

    # decode

    c = hamming_decode(hc_noise)
    print('\ndecode:')
    print(c)
