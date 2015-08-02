/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

#define ElementType Position
#define SIZE 8

struct Stack
{
	int Size;
	int Capacity;
	ElementType* Next;
};

typedef struct Stack* Stack;

Stack Initialize()
{
	Stack S;

	S = malloc(sizeof(struct Stack));
	S -> Size = 0;
	S -> Capacity = SIZE;
	S -> Next = malloc(sizeof(ElementType) * SIZE);

	return S;
}

int isEmpty(Stack S)
{
	return S -> Size == 0;
}

int isFull(Stack S)
{
	return S -> Size == S -> Capacity;
}

ElementType Pop(Stack S)
{
	if (isEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[--S -> Size];
}

void Push(Stack S, ElementType Value)
{
	if (isFull(S))
	{
		S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = Value;
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

struct RetRecord
{
	int* Buffer;
	int Size;
	int Capacity;
};

typedef struct RetRecord* Record;

Record InitializeRecord()
{
	Record R;

	R = malloc(sizeof(struct RetRecord));
	R -> Buffer = malloc(sizeof(int) * SIZE);
	R -> Capacity = SIZE;
	R -> Size = 0;

	return R;
}

void PushToRecord(Record R, int Value)
{
	if (R -> Size == R -> Capacity)
	{
		R -> Buffer = realloc(R -> Buffer, R -> Capacity * 2 * sizeof(int));
		R -> Capacity *= 2;
	}

	R -> Buffer[R -> Size++] = Value;
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) 
{
  if (root == NULL)
  {
  	*returnSize = 0;
  	return NULL;
  }

  Stack S;
  Position P;
	Record R;

  S = Initialize();
  R = InitializeRecord();
  Push(S, root);
		
  while(!isEmpty(S))
  {
  	P = Pop(S);

  	PushToRecord(R, P -> val);
  	// printf("%d ", P -> val);

  	if (P -> right)
  		Push(S, P -> right);

  	if (P -> left)
  		Push(S, P -> left);
  }

  *returnSize = R -> Size;
  return R -> Buffer;
}

int main(int argc, char const *argv[])
{
	Tree T;
	int Len, i, returnSize;
	int *Buffer;
	int Array[] = {8, 7, 4, 10, 9, 12};;

	T = NULL;
	Len = sizeof(Array) / sizeof(Array[0]);
	Len = 64;
	for (i = 0; i < Len; ++i)
		T = Insert(rand() % 1024, T);

	PreOrderTraverse(T);
	printf("\n");

	Buffer = preorderTraversal(T, &returnSize);
	printf("%d\n", returnSize);

	for (i = 0; i < returnSize; ++i)
		printf("%d ", Buffer[i]);
	printf("\n");
	return 0;
}