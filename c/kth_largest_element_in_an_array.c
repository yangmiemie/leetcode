// Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

// For example,
// Given [3,2,1,5,6,4] and k = 2, return 5.

// Note: 
// You may assume k is always valid, 1 ≤ k ≤ array's length.

#include <stdio.h>
#include <stdlib.h>

int GetMidValueOfIndex(int* Numbers, int Left, int Right)
{
	int Mid;

	Mid = (Left + Right) / 2;

	if (Numbers[Left] > Numbers[Right])
	{
		if (Numbers[Mid] >= Numbers[Left])
			return Left;
		else
		{
			if (Numbers[Mid] >= Numbers[Right])
				return Mid;
			else
				return Right;
		}
	}
	else
	{
		if (Numbers[Mid] >= Numbers[Right])
			return Right;
		else
		{
			if (Numbers[Mid] > Numbers[Left])
				return Mid;
			else
				return Left;
		}
	}
}

void Swap(int* Numbers, int i, int j)
{
	int Temp;

	Temp = Numbers[i];
	Numbers[i] = Numbers[j];
	Numbers[j] = Temp;
}

int Partition(int* Numbers, int Left, int Right)
{
	if (Numbers == NULL || Left > Right)
		return -1;

	if (Left == Right)
		return Left;

	int Pivot;
	int i, j;

	Pivot = GetMidValueOfIndex(Numbers, Left, Right);
	Swap(Numbers, Left, Pivot);

	i = Left + 1;
	j = Right;

	while (i <= j)
	{
		while (Numbers[i] < Numbers[Left]) ++i;
		while (Numbers[j] >= Numbers[Left] && j > Left) --j;

		if (i >= j)
			break;

		Swap(Numbers, i, j);
		++i;
		--j;
	}

	Swap(Numbers, Left, j);

	return j;
}

int findKthLargest(int* nums, int numsSize, int k) {
	int TargetIndex, Index, Left, Right;

	TargetIndex = numsSize - k;
	Left = 0;
	Right = numsSize - 1;
	while (1)
	{
		Index = Partition(nums, Left, Right);
		if (Index > TargetIndex)
			Right = Index - 1;
		else if (Index < TargetIndex)
			Left = Index + 1;
		else
			return nums[Index];
	}
}

void PrintArray(int* Numbers, int Size)
{
	int i;

	for (i = 0; i < Size; ++i)
		printf("%d ", Numbers[i]);
	printf("\n");
}

void QuickSort(int* Numbers, int Left, int Right)
{
	if (Left >= Right)
		return;

	int Pivot;

	Pivot = Partition(Numbers, Left, Right);
	QuickSort(Numbers, Left, Pivot - 1);
	QuickSort(Numbers, Pivot + 1, Right);
}

int main(int argc, char const *argv[])
{
	int i, Size, Index, Value;
	int *Numbers, *DupNumbers;
	int TestNumbers[] = {3,2,3,1,2,4,5,5,6};

	// Size = 16;
	// Numbers = malloc(sizeof(int) * Size);
	// DupNumbers = malloc(sizeof(int) * Size);
	// for (i = 0; i < Size; ++i)
	// {
	// 	Numbers[i] = 3;
	// 	DupNumbers[i] = Numbers[i];
	// }

	// PrintArray(Numbers, Size);
	// Index = Partition(Numbers, 0, Size - 1);
	// printf("%d\n", Index);

	// PrintArray(Numbers, Size);

	// QuickSort(DupNumbers, 0, Size - 1);

	// PrintArray(DupNumbers, Size);

	// for (i = 1; i <= Size; ++i)
	// {
	// 	Value = findKthLargest(Numbers, Size, i);
	// 	printf("%d ", Value);
	// }
	// printf("\n");

	Size = sizeof(TestNumbers) / sizeof(TestNumbers[0]);
	Value = findKthLargest(TestNumbers, Size, 4);
	printf("%d ", Value);
	return 0;
}