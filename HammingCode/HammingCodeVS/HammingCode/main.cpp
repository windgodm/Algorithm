#include <iostream>
#include "HammingCode.h"

using std::cin;
using std::cout;
using std::endl;
using std::hex;

int main()
{
    cout << "Hello World!\n";

    unsigned char m[] = { 0x42, 0x00, 0xc7, 0x9f, 0x0a, 0x1 };
    unsigned int mBytes = 6;
    unsigned char *c;
    unsigned int cBytes;
    unsigned char m_[10] = { 0, };
    
    HammingCode hc;

    // init

    hc.SetParityBitNum(6);

    hc.data = m;
    hc.dataBytesNum = mBytes;

    cBytes = hc.GetCodeBytesNum();
    c = (unsigned char*)malloc(cBytes);
    memset(c, 0, cBytes);

    hc.code = c;
    hc.codeBytesNum = cBytes;

    // encode

    hc.Encode();

    cout << "encode(hex little):\n";
    for (int i = 0; i < cBytes; i++) {
        cout << hex << (int)c[i] << " ";
    }
    cout << endl << endl;

    // decode

    hc.data = m_;
    hc.Decode();

    cout << "decode:\n";
    for (int i = 0; i < cBytes; i++) {
        cout << hex << (int)m_[i] << " ";
    }
    cout << endl << std::dec << *(unsigned long long*)m_;
    cout << endl << endl;

    return 0;
}
