// Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

// You may assume that the array is non-empty and the majority element always exist in the array.

#include <stdio.h>

int majorityElement(int* nums, int numsSize) {
	int Number, Value, i;

	if (nums == NULL || numsSize == 0)
		return 0;

	if (numsSize == 1)
		return nums[0];

	Number = 1;
	Value = nums[0];

	for (i = 1; i < numsSize; ++i)
	{
		if (Value != nums[i])
		{
			--Number;

			if ((Number == 0) && (i + 1 < numsSize))
			{
				Value = nums[++i];
				++Number;				
			}
		}
		else
		{
			++Number;
		}
	}

	return Value;
}

int main(int argc, char const *argv[])
{
	int Numbers[] = {2,2,1,1,1,2,2};

	printf("%d\n", majorityElement(Numbers, sizeof(Numbers) / sizeof(Numbers[0])));
	return 0;
}