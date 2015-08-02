// Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

// For example,
// Given n = 3, there are a total of 5 unique BST's.

//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

#include <stdio.h>
#include <stdlib.h>

int GetNumberTrees(int* Numbers, int n)
{
	if (Numbers[n] != -1)
		return Numbers[n];

	Numbers[n] = numTrees(n);
	return Numbers[n];
}

int numTrees(int n) {
 if (n == 0)
 	return 1;

 if (n == 1)
 	return 1;

 int i, Sum;
 int* Nums;

 Nums = malloc(sizeof(int) * n);
 for (i = 0; i < n; ++i)
 	Nums[i] = -1;

 Sum = 0;
 for (i = 0; i < n / 2; ++i)
 	Sum += GetNumberTrees(Nums, i) * GetNumberTrees(Nums, n - i - 1);

 Sum *= 2;
 if (n % 2 == 1)
 	Sum += GetNumberTrees(Nums, n / 2) * GetNumberTrees(Nums, n / 2);

 free(Nums);
 return Sum;
}

int main(int argc, char const *argv[])
{
	int n, i;

	n = 19;

	for (i = 0; i <= n; ++i)
		printf("%d: %d\n", i, numTrees(i));
	return 0;
}