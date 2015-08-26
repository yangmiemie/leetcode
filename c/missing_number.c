// Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

// For example,
// Given nums = [0, 1, 3] return 2.

// Note:
// Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

#include <stdio.h>

int missingNumber(int* nums, int numsSize) {
  int i;
  int Sum1, Sum2;

  if (nums == NULL)
    return 0;

  Sum1 = Sum2 = 0;
  for (i = 0; i < numsSize; ++i)
  {
    Sum1 += i;
    Sum2 += nums[i];
  }

  Sum1 += numsSize;

  return Sum1 - Sum2;
}

int main(int argc, char const *argv[])
{
  int Numbers[] = {0, 1, 3};

  printf("%d\n", missingNumber(Numbers, 3));
  return 0;
}