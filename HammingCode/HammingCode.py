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


def hamming_encode(x, n = 4):
    
    hc = 0
    l = 2 # l >= 3
    dataBitNum = (1<<n)-n-1
    for i in range(dataBitNum):
        if l & l+1 :             # if l != 2**n - 1
            l += 1
        else:                    # if l == 2**n - 1
            l += 2               # skip l=2**n
        hc |= (x & 1) << l
        x >>= 1

    sta = hamming_status(hc)
    for l in range(n):
        if sta & 1:
            hc |= 1 << (1 << l)  # hc |= 2**2**l
        sta >>= 1
    sta = hamming_status(hc)

    return hc


def hamming_encode_by_block(x, n = 4):

    # n is the number of check bit
    if n < 4:
        return None

    dataNum = (1<<n)-n-1 # number of data bit
    dataMask = ((1<<dataNum)-1) # (1<<dataNum)-1 = b111...
    bytesNum = 1<<(n-3) # = 2**n / 8

    hc = bytes(0)

    while x:
        
        hc += hamming_encode(x & dataMask, n).to_bytes(bytesNum, 'little')
        x >>= dataNum
    
    return hc


def hamming_decode(x, n = 4):

    i = 2 # i >= 3
    l = 0
    c = 0

    x >>= 3

    for i in range(3, 1<<n):

        if not i & (i-1): # if i == 2**n
            x >>= 1       # this is check(parity) bit
            continue

        if x & 1:
            c |= 1 << l
        
        l += 1
        x >>= 1

    return c

def hamming_decode_by_block(x, n = 4):
    
    dataNum = (1<<n)-n-1 # = 2**n-n-1, number of data bit
    bytesNum = 1<<(n-3) # = 2**n / 8, size of hamming code(bytes)
    l = 0
    c = 0
    x = [int.from_bytes(x[i:i+bytesNum], 'little') for i in range(0, len(x), bytesNum)]
    for m in x:
        # check
        sta = hamming_status(m)
        print('check:', sta)
        # fix
        m ^= 1 << sta
        # decode
        c |= hamming_decode(m, n) << l
        l += dataNum
    
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

    hc = hamming_encode_by_block(i, 4)
    print('hamming encode(hex little):')
    print(hc.hex())
    print()

    # noise

    hc_noise = bytes([hc[0] ^ 0x40]) + hc[1:]

    # decode

    c = hamming_decode_by_block(hc_noise, 4)
    print('\ndecode:')
    print(c)
