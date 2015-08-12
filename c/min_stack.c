// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

// push(x) -- Push element x onto stack.
// pop() -- Removes the element on top of the stack.
// top() -- Get the top element.
// getMin() -- Retrieve the minimum element in the stack.

#include <stdio.h>
#include <stdlib.h>

#include "lib/test_stack.h"

#define ElementType int

struct StackRecord 
{
	int Size;
	int Capacity;
	ElementType* Next;
};

typedef struct StackRecord* Stack;

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
	return S -> Size == S -> Capacity;
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

typedef struct {
  Stack S1, S2;  
} MinStack;

void minStackCreate(MinStack *stack, int maxSize) {
	stack -> S1 = Initialize(maxSize);
	stack -> S2 = Initialize(maxSize);
}

void minStackPush(MinStack *stack, int element) {
	int Min;

	Push(stack -> S1, element);

	if (IsEmpty(stack -> S2))
		Push(stack -> S2, element);
	else
	{
		Min = Top(stack -> S2);
		if (Min > element)
			Push(stack -> S2, element);
		else
			Push(stack -> S2, Min);
	}
}

void minStackPop(MinStack *stack) {
	Pop(stack -> S1);
	Pop(stack -> S2);
}

int minStackTop(MinStack *stack) {
	Top(stack -> S1);
}

int minStackGetMin(MinStack *stack) {
	Top(stack -> S2);
}

void minStackDestroy(MinStack *stack) {
	Destroy(stack -> S1);
	Destroy(stack -> S2);
}

int main(int argc, char const *argv[])
{
	int i, Value, Min;
	MinStack* stack;
	
	stack = malloc(sizeof(MinStack));
	minStackCreate(stack, 2);

	for (i = 0; i < 10; ++i)
		minStackPush(stack, rand() % 20);

	for (i = 0; i < 10; ++i)
	{
		Value = minStackTop(stack);
		Min = minStackGetMin(stack);
		printf("%d %d\n", Value, Min);
		minStackPop(stack);
	}

	printf("At last, %d, %d\n", IsEmpty(stack -> S1), IsEmpty(stack -> S2));
	return 0;
}