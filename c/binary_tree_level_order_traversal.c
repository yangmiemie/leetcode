// Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

// For example:
// Given binary tree {3,9,20,#,#,15,7},
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its bottom-up level order traversal as:
// [
//   [15,7],
//   [9,20],
//   [3]
// ]

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 2

typedef struct LevelReturnRecord* RetPtr;
typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;
typedef struct LevelOrderNode* LNode;
typedef struct QueueRecord* Queue;

#define ElementType LNode

struct TreeNode {
	int val;
 	struct TreeNode *left;
 	struct TreeNode *right;
};

struct LevelOrderNode 
{
	Position P;
	int Level;
};

struct QueueRecord {
	int rear;
	int front;
	ElementType *Array;
	int capacity;
};

struct LevelReturnRecord
{
	int** values;
	int* columnSizes;
	int* columnCapacity;
	int returnSize;
	int currX;
	int currY;
};

Queue Initialize(int size);
int isEmpty(Queue Q);
int Succ(Queue Q, int index);
int isFull(Queue Q);
ElementType Dequeue(Queue Q);
void Rearrange(Queue Q);
void Enqueue(Queue Q, ElementType value);
void Destroy(Queue Q);
LNode NewLNode(Position P, int isLast);
RetPtr InitializeRetRecord();
void PushToRetRecord(RetPtr Ptr, int value, int isLast);

Queue Initialize(int size)
{
	Queue Q;

	Q = malloc(sizeof(struct QueueRecord));
	Q -> rear = 0;
	Q -> front = 0;
	Q -> Array = malloc(sizeof(ElementType) * size);
	Q -> capacity = size;

	return Q;
}

int isEmpty(Queue Q)
{
	return Q -> front == Q -> rear;
}

int Succ(Queue Q, int index)
{
	if (++index >= Q -> capacity)
		return index % Q -> capacity;

	return index;
}

int isFull(Queue Q)
{
	return Succ(Q, Q -> front) == Q -> rear;
}

ElementType Dequeue(Queue Q)
{
	if (isEmpty(Q))
	{
		fprintf(stderr, "Empty Queue\n");
		exit(1);		
	}

	ElementType Value;
	Value = Q -> Array[Q -> rear];
	Q -> rear = Succ(Q, Q -> rear);

	return Value;
}

void Rearrange(Queue Q)
{
	ElementType *Buffer;
	ElementType Value;
	int i;

	Buffer = malloc(sizeof(ElementType) * Q -> capacity * 2);

	i = 0;
	while(!isEmpty(Q))
		Buffer[i++] = Dequeue(Q);

	free(Q -> Array);
	Q -> Array = Buffer;
	Q -> capacity = Q -> capacity * 2;
	Q -> rear = 0;
	Q -> front = i;
}

void Enqueue(Queue Q, ElementType value)
{
	if (isFull(Q))
		Rearrange(Q);

	Q -> Array[Q -> front] = value;
	Q -> front = Succ(Q, Q -> front);
}

ElementType Rear(Queue Q)
{
	if (isEmpty(Q))
	{
		fprintf(stderr, "Empty Queue\n");
		exit(1);		
	}

	return Q -> Array[Q -> rear];
}

void Destroy(Queue Q)
{
	free(Q -> Array);
	free(Q);
}

LNode NewLNode(Position P, int Level)
{
	LNode Node;

	Node = malloc(sizeof(struct LevelOrderNode));
	Node -> P = P;
	Node -> Level = Level;

	return Node;
}


RetPtr InitializeRetRecord()
{
	RetPtr Ptr;
	int i;

	Ptr = malloc(sizeof(struct LevelReturnRecord));
	Ptr -> returnSize = SIZE;

	Ptr -> values = malloc(sizeof(int*) * SIZE);
	for (i = 0; i < Ptr -> returnSize; ++i)
		Ptr -> values[i] = malloc(sizeof(int) * SIZE);

	Ptr -> columnCapacity = malloc(sizeof(int) * SIZE);
	for (i = 0; i <  SIZE; ++i)
		Ptr -> columnCapacity[i] = SIZE;

	Ptr -> columnSizes = malloc(sizeof(int) * SIZE);
	for (i = 0; i <  SIZE; ++i)
		Ptr -> columnSizes[i] = 0;

	Ptr -> currX = 0;
	Ptr -> currY = 0;
	return Ptr;
}

void PushToRetRecord(RetPtr Ptr, int value, int isLast)
{
	int i;

	if (Ptr -> currY >= Ptr -> returnSize)
	{
		Ptr -> values = realloc(Ptr -> values, Ptr -> returnSize * 2 * sizeof(int*));
		Ptr -> returnSize *= 2;

		Ptr -> columnCapacity = realloc(Ptr -> columnCapacity, sizeof(int) * Ptr -> returnSize);
		for (i = Ptr -> returnSize / 2; i <  Ptr -> returnSize; ++i)
			Ptr -> columnCapacity[i] = SIZE;

		Ptr -> columnSizes = realloc(Ptr -> columnSizes, sizeof(int) * Ptr -> returnSize);
		for (i = Ptr -> returnSize / 2; i <  Ptr -> returnSize; ++i)
			Ptr -> columnSizes[i] = 0;


		for (i = Ptr -> returnSize / 2; i < Ptr -> returnSize; ++i)
		{
			Ptr -> values[i] = malloc(sizeof(int) * SIZE);
		}
	}

	if (Ptr -> currX >= Ptr -> columnCapacity[Ptr -> currY])
	{
		Ptr -> values[Ptr -> currY] = realloc(Ptr -> values[Ptr -> currY], sizeof(int) * Ptr -> columnCapacity[Ptr -> currY] * 2);
		Ptr -> columnCapacity[Ptr -> currY] *= 2;
	}

	Ptr -> values[Ptr -> currY][Ptr -> currX++] = value;
	Ptr -> columnSizes[Ptr -> currY]++;

	if (isLast)
	{
		Ptr -> currX = 0;
		Ptr -> currY++;
	}
}

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if (root == NULL)
    {
    	*columnSizes = 0;
    	returnSize = 0;
    	return NULL;
    }

    Queue Q;
    ElementType Node;
    ElementType RearNode;
    RetPtr Record;
    int isLast;

    Q = Initialize(SIZE);
    Enqueue(Q, NewLNode(root, 0));

    Record = InitializeRetRecord();

    while(!isEmpty(Q))
    {
    	Node = Dequeue(Q);

    	if (isEmpty(Q))
    	{
    		isLast = 1;
    	}
    	else
    	{
    		RearNode = Rear(Q);

    		if (RearNode -> Level == Node -> Level)
    			isLast = 0;
    		else
    			isLast = 1;
    	}
	    // printf("%d ", Node -> P -> val);
    	
    	if (isLast)
    		PushToRetRecord(Record, Node -> P -> val, 1);
    	else
    		PushToRetRecord(Record, Node -> P -> val, 0);    		

    	if (Node -> P -> left != NULL)
    	{
	    	Enqueue(Q, NewLNode(Node -> P -> left, Node -> Level + 1));
    	}

    	if (Node -> P -> right != NULL)
    	{
	    	Enqueue(Q, NewLNode(Node -> P -> right, Node -> Level + 1));
    	}

    	free(Node);
    }

    Destroy(Q);
    *columnSizes = Record -> columnSizes;
    *returnSize = Record -> currX == 0 ?  Record -> currY : Record -> currY + 1;
    return Record -> values;
}

void testCase()
{
	// int Len, i;
	// int Array[] = {1, 2, 3, 4, 5, 6, 7, 8};
	// Queue Q;
	// ElementType Value;

	// Len = 8;
	// Q = Initialize(2);
	// for (i = 0; i < Len; ++i)
	// 	Enqueue(Q, Array[i]);

	// i = 0;
	// while(!isEmpty(Q))
	// 	assert(Dequeue(Q) == Array[i++]);		

}

Tree NewNode(int value)
{
	Tree T;
	T = malloc(sizeof(struct TreeNode));
	T -> val = value;
	T -> left = T -> right = NULL;
	return T;
}

Tree Insert(int value, Tree T)
{
	if (T == NULL)
		return NewNode(value);

	if (T -> val > value)
		T -> left = Insert(value, T -> left);
	else if (T -> val < value)
		T -> right = Insert(value, T -> right);

	return T;
}

void PreOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	printf("%d ", T -> val);
	PreOrderTraverse(T -> left);
	PreOrderTraverse(T -> right);
}

void PostOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	PostOrderTraverse(T -> left);
	PostOrderTraverse(T -> right);
	printf("%d ", T -> val);
}

int main(int argc, char const *argv[])
{
	Tree T;
	int Len, i, j, returnSize;
	int *columnSizes;
	int **values;
	// int array[] = {8, 7, 4, 10, 9, 12};
	int array[] = {-150, -149, -148, -147, -146, -145, -144, -143, -142};
	T = NULL;
	Len = sizeof(array) / sizeof(array[0]);
	// Len = 64;
	// for (i = 0; i < Len; ++i)
	// 	T = Insert(array[i], T);
	for (i = -105; i <= 600; ++i)
		T = Insert(i, T);
		// T = Insert(rand() % 1024, T);

	// PreOrderTraverse(T);
	// printf("\n");

	// PostOrderTraverse(T);
	// printf("\n");

	values = levelOrder(T, &columnSizes, &returnSize);

	// printf("\n");
	printf("returnSize = %d\n", returnSize);

	printf("columnSizes are ");
	for (i = 0; i < returnSize; ++i)
		printf("%d ", columnSizes[i]);
	printf("\n");

	for (i = 0; i < returnSize; ++i)
	{
		for (j = 0; j < columnSizes[i]; ++j)
			printf("%d ", values[i][j]);
		printf("\n");
	}
	return 0;
}
