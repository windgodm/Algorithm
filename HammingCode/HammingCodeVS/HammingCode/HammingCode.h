#pragma once

#ifndef _HAMMINGCODE_H_
#define _HAMMINGCODE_H_

class HammingCode
{
private:
	unsigned char parityBitNum;
	unsigned int dataNum;  // number of data bit
	unsigned int dataMask; // (1<<dataNum)-1 = b111...
	unsigned int bytesNum; // size of each hamming code(bytes)
public:
	unsigned char* data;
	unsigned int dataBytesNum; // number of data(bytes)
	unsigned char* code;
	unsigned int codeBytesNum; // number of code(bytes)
	
public:
	HammingCode();
	HammingCode(unsigned char* data, unsigned int dataBytesNum, unsigned char* code, unsigned int codeBytesNum, unsigned char parityBitNum);
	void SetParityBitNum(unsigned char parityBitNum);
	unsigned int GetDataBytesNum();
	unsigned int GetCodeBytesNum();
	unsigned int Check();
	void Encode();
	void Decode();
};

#endif // _HAMMINGCODE_H_