// Given an array of integers, every element appears twice except for one. Find that single one.

// Note:
// Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
	if (nums == NULL || numsSize == 0)
		return 0;

	int Result, i;

	Result = 0;
	for (i = 0; i < numsSize; ++i)
		Result ^= nums[i];

	return Result;
}

int main(int argc, char const *argv[])
{
	int Numbers[] = {1, 2, 3, 2, 1};

	printf("%d\n", singleNumber(Numbers, sizeof(Numbers) / sizeof(Numbers[1])));
	return 0;
}