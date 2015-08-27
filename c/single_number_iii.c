// Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

// For example:

// Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

// Note:
// The order of the result is not important. So in the above example, [5, 3] is also correct.
// Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 64

int* singleNumber(int* nums, int numsSize, int* returnSize) {
	int i, j, m, n, Sum, Value;
	int *Numbers1, *Numbers2, *Result;

	if (nums == NULL || numsSize == 0)
	{
		returnSize = 0;
		return NULL;
	}

	Sum = 0;
	for (i = 0; i < numsSize; ++i)
		Sum ^= nums[i];

	for (i = 0; i < WORD_LENGTH; ++i)
		if (Sum & 0x01 == 1)
			break;
		else
			Sum = Sum >> 1;

	for (j = 0, Value = 1; j < i; ++j)
		Value = Value << 1;

	Numbers1 = malloc(sizeof(int) * numsSize);
	Numbers2 = malloc(sizeof(int) * numsSize);
	memset(Numbers1, 0, sizeof(int) * numsSize);
	memset(Numbers2, 0, sizeof(int) * numsSize);

	m = n = 0;
	for (i = 0; i < numsSize; ++i)
	{
		if ((nums[i] & Value) != 0)
			Numbers1[m++] = nums[i];
		else
			Numbers2[n++] = nums[i];
	}

	Result = malloc(sizeof(int) * 2);
	memset(Result, 0, sizeof(int) * 2);
	
	for (i = 0; i < m; ++i)
		Result[0] ^= Numbers1[i];

	for (i = 0; i < n; ++i)
		Result[1] ^= Numbers2[i];

	free(Numbers1);
	free(Numbers2);

	*returnSize = 2;
	return Result;
}

int main(int argc, char const *argv[])
{
	// int Numbers[] = {1, 2, 1, -3, 2, 5};
	int Numbers[] = {1403617094,-490450406,-1756388866,-967931676,1878401007,1878401007,-74743538,1403617094,-1756388866,-74743538,-490450406,-1895772685};
	// int Numbers[] = {2, 3, 3, 2, 1, 4};
	int i, ReturnSize, *Nums;
 
	Nums = singleNumber(Numbers, sizeof(Numbers) / sizeof(Numbers[0]), &ReturnSize);

	for (i = 0; i < ReturnSize; ++i)
		printf("%d ", Nums[i]);
	printf("\n");
	return 0;
}