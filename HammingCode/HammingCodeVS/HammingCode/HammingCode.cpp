#include "HammingCode.h"

HammingCode::HammingCode()
{
	SetParityBitNum(4);
	data = nullptr;
	dataBytesNum = 0;
	code = nullptr;
	codeBytesNum = 0;
}

HammingCode::HammingCode(unsigned char* data, unsigned int dataBytesNum, unsigned char* code, unsigned int codeBytesNum, unsigned char parityBitNum)
{
	SetParityBitNum(parityBitNum);
	this->data = data;
	this->dataBytesNum = dataBytesNum;
	this->code = code;
	this->codeBytesNum = codeBytesNum;
}

void HammingCode::SetParityBitNum(unsigned char parityBitNum)
{
	this->parityBitNum = parityBitNum;
	dataNum = (1 << parityBitNum) - parityBitNum - 1;
	dataMask = ((1 << dataNum) - 1);
	bytesNum = 1 << (parityBitNum - 3);
}

unsigned int HammingCode::GetDataBytesNum()
{
	// todo
	return codeBytesNum;
}

unsigned int HammingCode::GetCodeBytesNum()
{
	return (((dataBytesNum << 3) - 1) / dataNum + 1) << (parityBitNum - 3);
}

unsigned int HammingCode::Check()
{
	if (code == 0)
		return 0;

	unsigned int status = 0;
	unsigned int i, j, index;
	unsigned char temp;
	
	for (i = 0; i < codeBytesNum; i++) {
		temp = code[i];
		for (j = 0, index = i << 3; j < 8; j++, index++, temp >>= 1) {
			if (temp & 1) {
				status ^= index;
			}
		}
	}

	return status;
}

void HammingCode::Encode()
{
	if (data == 0 || code == 0)
		return;

	unsigned int status = 0, codeNum = 1 << parityBitNum;
	unsigned int codeBytesNum = GetCodeBytesNum();
	unsigned int codeByte = 0, codeBit = 3, index = 3;
	unsigned char temp = data[0];
	unsigned int dataByte = 0, dataBit = 0;

	while (codeByte < codeBytesNum) {
		// get data

		if (dataBit == 8) {
			dataBit = 0;
			if (++dataByte < dataBytesNum)
				temp = data[dataByte];
			else
				temp = 0;
		}

		// copy data to code and update status

		if (temp & 1) {
			code[codeByte] |= 1 << codeBit;
			status ^= index;
		}
		dataBit++;
		temp >>= 1;

		// update code bit index

		codeBit++;
		index++;
		// skip index == 2**n
		for (; (index & (index - 1)) == 0; codeBit++, index++);

		// update code byte index

		if (codeBit >= 8) {
			codeBit -= 8;
			codeByte++;
		}

		// set parity bits
		if (index >= codeNum) {
			index = 0;
			for (int i = 0; i < parityBitNum; i++, status >>= 1) {
				if (status & 1) {
					// parity bit at position 2**i should be 1
					int j = 1 << i; // parity bit position
					code[codeByte - bytesNum + (j >> 3)] |= 1 << (j & 7);
				}
			}
			codeBit = 3;
			index = 3;
			status = 0;
		}
	}
}

void HammingCode::Decode()
{
	if (data == 0 || code == 0)
		return;

	unsigned int status = 0, codeNum = 1 << parityBitNum;
	unsigned int codeByte = 0, codeBit = 3, index = 3;
	unsigned int temp = code[0]; // fix
	unsigned int dataByte = 0, dataBit = 0;

	for (codeByte = 0; codeByte < codeBytesNum;) {

		index = 0;

		for (int i = 0; i < bytesNum; i++, codeByte++) {

			temp = code[codeByte];

			for (int j = 0; j < 8; j++, temp >>= 1, index++) {

				// copy code to data

				if (index & (index - 1)) {

					if (temp & 1) {
						data[dataByte] |= 1 << dataBit;
					}

					dataBit++;
					if (dataBit == 8) {
						dataBit = 0;
						dataByte++;
					}
				}
			}
		}
	}
}
