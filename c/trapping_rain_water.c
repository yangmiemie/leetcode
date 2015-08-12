// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

// For example, 
// Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define MAX 8

struct StackRecord
{
	int Size;
	int Capacity;
	ElementType *Next;
};

typedef struct StackRecord * Stack;

Stack Initialize(int Capacity)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = Capacity;
	S -> Next = malloc(sizeof(ElementType) * Capacity);

	return S;
}

int IsEmpty(Stack S)
{
	return S -> Size == 0;
}

int IsFull(Stack S)
{
	return S -> Capacity == S -> Size;
}

void Push(Stack S, ElementType Value)
{
	if (IsFull(S))
	{
		S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = Value;
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[--S -> Size];
}

ElementType Top(Stack S)
{
	if (IsEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[S -> Size - 1];
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

struct MaxStackRecord
{
	Stack S1, S2;
};

typedef struct MaxStackRecord* MaxStack;

MaxStack CreateMaxStack(int Capacity)
{
	MaxStack MS;

	MS = malloc(sizeof(struct MaxStackRecord));
	MS -> S1 = Initialize(Capacity);
	MS -> S2 = Initialize(Capacity);
	return MS;
}

void PushMaxStack(MaxStack MS, ElementType Value)
{
	ElementType MaxValue;

	if (IsEmpty(MS -> S1))
	{
		Push(MS -> S1, Value);
		Push(MS -> S2, Value);
		return;
	}

	MaxValue = Top(MS -> S2);
	if (MaxValue < Value)
		Push(MS -> S2, Value);
	else
		Push(MS -> S2, MaxValue);

	Push(MS -> S1, Value);
}

void PopMaxStack(MaxStack MS)
{
	Pop(MS -> S1);
	Pop(MS -> S2);
}

ElementType TopOfMaxStack(MaxStack MS)
{
	return Top(MS -> S1);
}

ElementType GetMaxValue(MaxStack MS)
{
	return Top(MS -> S2);
}

void DestroyMaxStack(MaxStack MS)
{
	Destroy(MS -> S1);
	Destroy(MS -> S2);
}

int trap(int* height, int heightSize) {
	if (heightSize <= 2)
		return 0;

	MaxStack MSLeft, MSRight;
	int i;
	int Bars, MaxRight, MaxLeft;

	MSLeft = CreateMaxStack(MAX);
	MSRight = CreateMaxStack(MAX);

	// PushMaxStack(MSLeft, height[0]);
	for (i = heightSize - 1; i >= 1; --i)
		PushMaxStack(MSRight, height[i]);

	Bars = 0;
	for (i = 1; i < heightSize - 1; ++i)
	{
		PushMaxStack(MSLeft, height[i-1]);
		PopMaxStack(MSRight);

		MaxLeft = GetMaxValue(MSLeft);
		MaxRight = GetMaxValue(MSRight);

		if (height[i] < MaxLeft && height[i] < MaxRight)
		{
			if (MaxRight < MaxLeft)
				Bars += MaxRight - height[i];
			else
				Bars += MaxLeft - height[i];
		}
	}

	return Bars;
}

int main(int argc, char const *argv[])
{
	int TrapNum[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	// int TrapNum[] = {2,0,2};
	int Len;

	Len = sizeof(TrapNum) / sizeof(TrapNum[0]);

	printf("%d\n", trap(TrapNum, Len));
	return 0;
}