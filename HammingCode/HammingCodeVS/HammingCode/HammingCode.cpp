#include "HammingCode.h"

HammingCode::HammingCode()
{
	SetParityBitNum(4);
	data = nullptr;
	dataBufBytes = 0;
	code = nullptr;
	codeBufBytes = 0;
}

HammingCode::HammingCode(unsigned char* data, unsigned int dataBufBytes, unsigned char* code, unsigned int codeBufBytes, unsigned char parityBitNum)
{
	SetParityBitNum(parityBitNum);
	this->data = data;
	this->dataBufBytes = dataBufBytes;
	this->code = code;
	this->codeBufBytes = codeBufBytes;
}

void HammingCode::SetParityBitNum(unsigned char parityBitNum)
{
	this->parityBitNum = parityBitNum;
	dataBits = (1 << parityBitNum) - parityBitNum - 1;
	dataMask = ((1 << dataBits) - 1);
	codeBytes = 1 << (parityBitNum - 3);
}

unsigned int HammingCode::GetDataBufBytes()
{
	// ceil((codeBufBytes * dataBits) / (2**parityBitNum))
	return (((codeBufBytes * dataBits) - 1) >> parityBitNum) + 1;
}

unsigned int HammingCode::GetCodeBufBytes()
{
	// ceil((dataBufBytes * 8) / dataBits) * (2**parityBitNum) / 8
	return (((dataBufBytes << 3) - 1) / dataBits + 1) << (parityBitNum - 3);
}

unsigned int HammingCode::Check()
{
	if (code == 0)
		return 0;

	unsigned int status = 0;
	unsigned int i, j, index;
	unsigned char temp;
	
	for (i = 0; i < codeBufBytes; i++) {
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
	unsigned int codeBufBytes = GetCodeBufBytes();
	unsigned int codeByte = 0, codeBit = 3, index = 3;
	unsigned char temp = data[0];
	unsigned int dataByte = 0, dataBit = 0;

	while (codeByte < codeBufBytes) {
		// get data

		if (dataBit == 8) {
			dataBit = 0;
			if (++dataByte < dataBufBytes)
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
					code[codeByte - codeBytes + (j >> 3)] |= 1 << (j & 7);
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

	for (codeByte = 0; codeByte < codeBufBytes;) {

		index = 0;

		for (int i = 0; i < codeBytes; i++, codeByte++) {

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
