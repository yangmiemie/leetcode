// Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

// For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.

#include <stdio.h>

int hammingWeight(int n) {
	int i;

	if (n == 0)
		return 0;

	i = 1;
	while ((n = (n & (n - 1))) != 0)
		++i;

	return i;
}

int main(int argc, char const *argv[])
{
	int N;

	N = -1;

	printf("%d\n", hammingWeight(N));
	printf("%d\n", sizeof(int));
	return 0;
}