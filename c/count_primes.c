// Description:

// Count the number of prime numbers less than a non-negative number, n.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2
typedef struct DynamicArray* DynArray;

struct DynamicArray
{
	int* Next;
	int Capacity;
	int Size;
};

int IsPrime(int N)
{
	int i;

	for (i = 2; i * i <= N; ++i)
	{
		if (N % i == 0)
			return 0;
	}

	return 1;
}

int countPrimes1(int n) {
	int i, Number;

	for (Number = 0, i = 2; i < n; ++i)
	{
		if (IsPrime(i) == 1)
			++Number;
	}

	return Number;
}

DynArray Initialize(int Capacity)
{
	DynArray DA;

	DA = malloc(sizeof(struct DynamicArray));
	DA -> Capacity = Capacity;
	DA -> Size = 0;
	DA -> Next = malloc(sizeof(int) * Capacity);

	return DA;
}

void AddToArray(DynArray DA, int Value)
{
	if (DA -> Size == DA -> Capacity)
	{
		DA -> Next = realloc(DA -> Next, 2 * DA -> Capacity * sizeof(int));
		DA -> Capacity *= 2;
	}

	DA -> Next[DA -> Size++] = Value;
}

int* GetAllFactors(int N, int* PtrSize)
{
	int i;
	DynArray DA;

	DA = Initialize(MAX);
	for (i = 2; i * i <= N; ++i)
	{
		if (IsPrime(i) == 1)
			AddToArray(DA, i);
	}

	*PtrSize = DA -> Size;
	return DA -> Next;
}

int countPrimes2(int n)
{
	int *Buffer, *Factors;
	int Size, Number, i, j;

	Buffer = malloc(sizeof(int) * n);
	memset(Buffer, 0, n * sizeof(int));

	Factors = GetAllFactors(n, &Size);

	for (i = 0; i < Size; ++i)
	{
		j = Factors[i];
		while (j * Factors[i] < n)
		{
			Buffer[j * Factors[i]] = 1;
			++j;
		}
	}

	for (Number = 0, i = 2; i < n; ++i)
	{
		if (Buffer[i] == 0)
			Number++;
	}

	free(Factors);
	free(Buffer);
	return Number;
}

int countPrimes(int n)
{
	int *Buffer;
	int Number, i, j;

	Buffer = malloc(sizeof(int) * n);
	memset(Buffer, 0, n * sizeof(int));

	for (i = 2; i * i <= n; ++i)
	{
		if (!IsPrime(i))
			continue;
			
		for (j = i; j * i < n; ++j)
		{
			Buffer[i * j] = 1;
		}
	}

	for (Number = 0, i = 2; i < n; ++i)
	{
		if (Buffer[i] == 0)
			Number++;
	}

	free(Buffer);
	return Number;
}

int main(int argc, char const *argv[])
{
	int N;

	N = 100;

	printf("%d\n", countPrimes(N));
	return 0;
}