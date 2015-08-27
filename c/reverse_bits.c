// Reverse bits of a given 32 bits unsigned integer.

// For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

#include <stdio.h>

#define WORD_LENGTH 32

int reverseBits(int n) {
	if (n == 0)
		return 0;

	int Result, i;

	Result = 0;

	for (i = 0; i < WORD_LENGTH; ++i)
	{
		Result = (Result << 1) | (n & 0x01);
		n = n >> 1;
	}

	return Result;
}

int main(int argc, char const *argv[])
{
	int N;

	N = -2;
	// N = 2;
	printf("%d\n", reverseBits(N));
	return 0;
}