// Implement the following operations of a stack using queues.

// push(x) -- Push element x onto stack.
// pop() -- Removes the element on top of the stack.
// top() -- Get the top element.
// empty() -- Return whether the stack is empty.
// Notes:
// You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
// Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
// You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).

#include <stdio.h>
#include <stdlib.h>

#define ElementType int

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType* Next;
};

typedef struct QueueRecord* Queue;

Queue Initialize(int Capacity)
{
	Queue Q;

	Q = malloc(sizeof(struct QueueRecord));
	Q -> Capacity = Capacity;
	Q -> Front = 0;
	Q -> Rear = 0;
	Q -> Next = malloc(sizeof(ElementType) * Q -> Capacity);
	Q -> Size = 0;

	return Q;
}

int Size(Queue Q)
{
	return Q -> Size;
}

int Succ(Queue Q, int Index)
{
	if (++Index >= Q -> Capacity)
		return Index % Q -> Capacity;

	return Index;
}

int IsEmpty(Queue Q)
{
	return Q -> Front == Q -> Rear;
}

int IsFull(Queue Q)
{
	return Succ(Q, Q -> Rear) == Q -> Front;
}

ElementType Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		fprintf(stderr, "Empty Queue\n");
		exit(1);
	}

	int Index;
	-- Q -> Size;
	Index = Q -> Front;
	Q -> Front = Succ(Q, Q -> Front);
	return Q -> Next[Index];
}

ElementType Front(Queue Q)
{
	if (IsEmpty(Q))
	{
		fprintf(stderr, "Empty Queue\n");
		exit(1);
	}

	return Q -> Next[Q -> Front];
}

Queue Rearrange(Queue Q)
{
	ElementType* Buffer = malloc(sizeof(ElementType) * Q -> Capacity * 2);
	int i;

	i = 0;
	while (!IsEmpty(Q))
		Buffer[i++] = Dequeue(Q);

	Q -> Capacity *= 2;
	Q -> Front = 0;
	Q -> Rear = i;
	free(Q -> Next);
	Q -> Next = Buffer;
	Q -> Size = i;

	return Q;
}

void Enqueue(Queue Q, ElementType Value)
{
	if (IsFull(Q))
		Q = Rearrange(Q);

	++ Q -> Size;
	Q -> Next[Q -> Rear] = Value;
	Q -> Rear = Succ(Q, Q -> Rear);
}

void Destroy(Queue Q)
{
	free(Q -> Next);
	free(Q);
}

struct Stack {
  Queue Q1, Q2;	
};

typedef struct {
  Queue Q1, Q2;
} Stack;

/* Create a stack */
void stackCreate(Stack *stack, int maxSize) {
	stack -> Q1 = Initialize(maxSize);
	stack -> Q2 = Initialize(maxSize);
}

Queue getQueueWithData(Stack *stack)
{
	if (IsEmpty(stack -> Q1))
		return stack -> Q2;
	else
		return stack -> Q1;
}

/* Push element x onto stack */
void stackPush(Stack *stack, int element) {
	Enqueue(getQueueWithData(stack), element);
}

/* Removes the element on top of the stack */
void stackPop(Stack *stack) {
	if (IsEmpty(stack -> Q1))
	{
		while (Size(stack -> Q2) != 1)
		{
			Enqueue(stack -> Q1, Dequeue(stack -> Q2));
		}

		Dequeue(stack -> Q2);
	}
	else
	{
		while (Size(stack -> Q1) != 1)
		{
			Enqueue(stack -> Q2, Dequeue(stack -> Q1));
		}

		Dequeue(stack -> Q1);
	}
}

/* Get the top element */
int stackTop(Stack *stack) {
	ElementType Value;

	if (IsEmpty(stack -> Q1))
	{
		while (Size(stack -> Q2) != 1)
		{
			Enqueue(stack -> Q1, Dequeue(stack -> Q2));
		}

		Value = Front(stack -> Q2);
		Enqueue(stack -> Q1, Dequeue(stack -> Q2));
	}
	else
	{
		while (Size(stack -> Q1) != 1)
		{
			Enqueue(stack -> Q2, Dequeue(stack -> Q1));
		}

		Value = Front(stack -> Q1);
		Enqueue(stack -> Q2, Dequeue(stack -> Q1));
	}

	return Value;
}

/* Return whether the stack is empty */
int stackEmpty(Stack *stack) {
	return IsEmpty(stack -> Q1) && IsEmpty(stack -> Q2);
}

/* Destroy the stack */
void stackDestroy(Stack *stack) {
	Destroy(stack -> Q1);
	Destroy(stack -> Q2);   
}

int TestStack()
{
 Stack* S;
 int i;

 S = malloc(sizeof(struct Stack));
 stackCreate(S, 2);

 for (i = 0; i < 100; ++i)
   stackPush(S, i);

 while (!stackEmpty(S))
 {
   printf("%d ", stackTop(S));
   stackPop(S); 	
 }

 printf("\n");

 stackDestroy(S);
}


int main(int argc, char const *argv[])
{
	TestStack();
	return 0;
}