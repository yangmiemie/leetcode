// Given an integer, write a function to determine if it is a power of two.

#include <stdio.h>

int isPowerOfTwo(int n) {
	if (n <= 0)
		return 0;

	return (n & (n - 1)) == 0;
}

int main(int argc, char const *argv[])
{
	int N;

	N = 9;
	printf("%d\n", isPowerOfTwo(N));
	return 0;
}