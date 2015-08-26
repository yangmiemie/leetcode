// Given an array of integers, every element appears three times except for one. Find that single one.

// Note:
// Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

#include <stdio.h>

#define BITS_LENGTH 64

int singleNumber(int* nums, int numsSize) {
	int Bits[BITS_LENGTH] = {0};
	int i, j, Number;

	for (i = 0; i < numsSize; ++i)
	{

		for (j = 0; j < BITS_LENGTH; ++j)
		{
			Bits[BITS_LENGTH - 1 - j] += (nums[i] & 0x01);
			nums[i] = nums[i] >> 1;

			if (nums[i] == 0)
				break;
		}
	}

	Number = 0;
	for (i = 0; i < BITS_LENGTH; ++i)
	{
		Number = Number << 1;
		if (Bits[i] % 3 != 0)
			Number |= 1;
	}

	return Number;
}

int main(int argc, char const *argv[])
{
	int Numbers[] = {0,0,0,5};
	printf("%d\n", singleNumber(Numbers, sizeof(Numbers) / sizeof(Numbers[0])));

	return 0;
}