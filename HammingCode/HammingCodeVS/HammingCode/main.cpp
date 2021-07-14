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
    unsigned char* m_;
    unsigned int m_Bytes;
    
    HammingCode hc;

    // Init

    hc.SetParityBitNum(4);

    // Encode

    // 1. Set data
    hc.data = m;
    hc.dataBufBytes = mBytes;

    // 2. Malloc memory for code
    cBytes = hc.GetCodeBufBytes();
    c = (unsigned char*)malloc(cBytes);
    memset(c, 0, cBytes);

    // 3. Set code
    hc.code = c;
    hc.codeBufBytes = cBytes;

    // 4. Encode
    hc.Encode();

    // debug
    cout << "encode(hex little):\n";
    for (int i = 0; i < cBytes; i++) {
        cout << hex << (int)c[i] << " ";
    }
    cout << endl << endl;

    // Decode

    // 1. Set code
    // pass

    // 2. Malloc memory for data
    m_Bytes = hc.GetDataBufBytes();
    m_ = (unsigned char*)malloc(m_Bytes);
    memset(m_, 0, m_Bytes);

    // 3. Set data
    hc.data = m_;
    hc.dataBufBytes = m_Bytes;

    // 4. Decode
    hc.Decode();

    // debug
    cout << "decode:\n";
    for (int i = 0; i < m_Bytes; i++) {
        cout << hex << (int)m_[i] << " ";
    }
    cout << endl << std::dec << *(unsigned long long*)m_;
    cout << endl << endl;

    return 0;
}
