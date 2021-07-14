#pragma once

#ifndef _HAMMINGCODE_H_
#define _HAMMINGCODE_H_

class HammingCode
{
private:
	unsigned char parityBitNum;
	unsigned int dataBits;  // size of each block of data(bit)
	unsigned int dataMask; // (1<<dataBits)-1 = b111...
	unsigned int codeBytes; // size of each hamming code(bytes)
public:
	unsigned char* data;
	unsigned int dataBufBytes; // size of data(bytes)
	unsigned char* code;
	unsigned int codeBufBytes; // size of code(bytes)
	
public:
	HammingCode();
	HammingCode(unsigned char* data, unsigned int dataBytesNum, unsigned char* code, unsigned int codeBytesNum, unsigned char parityBitNum);
	void SetParityBitNum(unsigned char parityBitNum);
	unsigned int GetDataBufBytes();
	unsigned int GetCodeBufBytes();
	unsigned int Check();
	void Encode();
	void Decode();
};

#endif // _HAMMINGCODE_H_
