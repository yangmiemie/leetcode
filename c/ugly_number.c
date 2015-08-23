// Write a program to check whether a given number is an ugly number.

// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

// Note that 1 is typically treated as an ugly number.

#include <stdio.h>

#define FIVE 5
#define TWO 2
#define THREE 3

int Divideable(int Number)
{
	if (Number % FIVE == 0)
		return FIVE;
	else if (Number % TWO == 0)
		return TWO;
	else if (Number % THREE == 0)
		return THREE;
	else
		return -1;
}

int isUgly(int num) {
	if (num <= 0)
		return 0;

	int Factor;

	while (num != 1)
	{
		Factor = Divideable(num);
		if (Factor == -1)
			return 0;

		num /= Factor;
	}

	return 1;
}

int main(int argc, char const *argv[])
{
	int Number;

	Number = 1;
	printf("%d\n", isUgly(Number));
	return 0;
}