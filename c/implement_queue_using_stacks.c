// Implement the following operations of a queue using stacks.

// push(x) -- Push element x to the back of queue.
// pop() -- Removes the element from in front of queue.
// peek() -- Get the front element.
// empty() -- Return whether the queue is empty.
// Notes:
// You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
// Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
// You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

#include <stdio.h>
#include <stdlib.h>

#define ElementType int

struct StackRecord 
{
	int Size;
	int Capacity;
	ElementType *Next;
};

typedef struct StackRecord* Stack;

Stack Initialize(int Capacity)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = Capacity;
	S -> Next = malloc(sizeof(ElementType) * S -> Capacity);

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

struct Queue {
	Stack S1, S2;
};

typedef struct {
	Stack S1, S2;    
} Queue;

/* Create a queue */
void queueCreate(Queue *queue, int maxSize) {
	queue -> S1 = Initialize(maxSize);	
	queue -> S2 = Initialize(maxSize);	
}

/* Push element x to the back of queue */
void queuePush(Queue *queue, int element) {
	Push(queue -> S1, element); 
}

void adjustQueue(Queue* queue)
{
	while (!IsEmpty(queue -> S1))
	{
		Push(queue -> S2, Pop(queue -> S1));
	}
}

/* Removes the element from front of queue */
void queuePop(Queue *queue) {
	if (IsEmpty(queue -> S2))
		adjustQueue(queue);

	Pop(queue -> S2);
}

/* Get the front element */
int queuePeek(Queue *queue) {
	if (IsEmpty(queue -> S2))
		adjustQueue(queue);

	Top(queue -> S2);
}

/* Return whether the queue is empty */
int queueEmpty(Queue *queue) {
	return IsEmpty(queue -> S1) && IsEmpty(queue -> S2);
}

/* Destroy the queue */
void queueDestroy(Queue *queue) {
	Destroy(queue -> S1);
	Destroy(queue -> S2);
}

int TestQueue()
{
 Queue* Q;
 int i;

 Q = malloc(sizeof(struct Queue));
 
 queueCreate(Q, 10);
 for (i = 0; i < 100; ++i)
   queuePush(Q, i);

 while (!queueEmpty(Q))
 {
 	 printf("%d ", queuePeek(Q));
   queuePop(Q);
 }
  
 printf("\n");

 queueDestroy(Q);
}

int main(int argc, char const *argv[])
{
	TestQueue();	
	return 0;
}