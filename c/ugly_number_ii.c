// Write a program to find the n-th ugly number.

// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

// Note that 1 is typically treated as an ugly number.

#include <stdio.h>

int GetMinOfThreeNum(int a, int b, int c)
{
	if (a > b)
	{
		if (b < c)
			return b;
		else
			return c;
	}
	else
	{
		if (a < c)
			return a;
		else
			return c;
	}
}

int nthUglyNumber(int n) {
	if (n == 1)
		return 1;

	if (n == 2)
		return 2;

	if (n == 3)
		return 3;

	int N1, N2, N3, N4;
	int i;

	i = 3;
	N1 = 1;
	N2 = 2;
	N3 = 3;

	while (i != n)
	{
		N4 = GetMinOfThreeNum(5 * N1, 3 * N2, 2 * N3);
		N1 = N2;
		N2 = N3;
		N3 = N4;
		++i;
	}

	return N4;
}

// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 
int main(int argc, char const *argv[])
{
	int i, n;

	n = 10;

	for (i = 1; i <= n; ++i)
		printf("%d ", nthUglyNumber(i));
	printf("\n");
	return 0;
}