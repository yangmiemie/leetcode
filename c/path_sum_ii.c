// Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

// For example:
// Given the below binary tree and sum = 22,
//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \    / \
//         7    2  5   1
// return
// [
//    [5,4,11,2],
//    [5,8,4,5]
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

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

#define SIZE 2
#define ElementType int

struct StackRecord
{
	int Size;
	int Capacity;
	ElementType* Next;
};

typedef struct StackRecord* Stack;

Stack Initialize()
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = SIZE;
	S -> Next = malloc(sizeof(ElementType) * S -> Capacity);

	return S;
}

int IsFull(Stack S)
{
	return S -> Size == S -> Capacity;
}

int IsEmpty(Stack S)
{
	return S -> Size == 0;
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

void Push(Stack S, ElementType X)
{
	if (IsFull(S))
	{
		S -> Next = realloc(S -> Next, S -> Capacity * 2 * sizeof(ElementType));
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = X;
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

struct PathSumRecord
{
	int* ColumnSizes;
	int Size;
	int Capacity;
	int** Next;
};

typedef struct PathSumRecord* PSR;

PSR InitializePSR()
{
	PSR P;

	P = malloc(sizeof(struct PathSumRecord));
	P -> Size = 0;
	P -> Capacity = SIZE;
	P -> ColumnSizes = malloc(sizeof(int) * P -> Capacity);
	P -> Next = malloc(sizeof(int*) * P -> Capacity);

	return P;
}

void AddValuesToPSR(PSR P, int* Values, int Size)
{
	if (P -> Capacity == P -> Size)
	{
		P -> Next = realloc(P -> Next, sizeof(int*) * 2 * P -> Capacity);
		P -> Capacity *= 2;
		P -> ColumnSizes = realloc(P -> ColumnSizes, sizeof(int*) * 2 * P -> Capacity);
	}

	int i;
	int* BUffer;

	BUffer = malloc(sizeof(int) * Size);
	for (i = 0; i < Size; ++i)
		BUffer[i] = Values[i];

	P -> Next[P -> Size] = BUffer;
	P -> ColumnSizes[P -> Size] = Size;
	++ P -> Size;
}

int PS(struct TreeNode* root, int sum, PSR P, Stack S) {
	if (root == NULL)
		return 0;

	if (root -> left == NULL && root -> right == NULL)
	{
		if (sum == root -> val)
		{
			Push(S, root -> val);
			AddValuesToPSR(P, S -> Next, S -> Size);
			Pop(S);
			return 1;
		}
		else
		{
			return 0;
		}
	}

	int LeftFound, RightFound;

	Push(S, root -> val);

	if (root -> left)
		LeftFound = PS(root -> left, sum - root -> val, P, S);

	if (root -> right)
		RightFound = PS(root -> right, sum - root -> val, P, S);

	Pop(S);
	return LeftFound || RightFound;	
}

int** pathSum(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {
	if (root == NULL)
	{
		*columnSizes = NULL;
		*returnSize == 0;
		return NULL;
	}

	PSR P;
	Stack S;
	int Found;

	P = InitializePSR();
	S = Initialize();

	Found = PS(root, sum, P, S);

	if (Found)
	{
		*columnSizes = P -> ColumnSizes;
		*returnSize = P -> Size;
		return P -> Next;		
	}
	else
	{
		columnSizes = NULL;
		returnSize == 0;
		return NULL;
	}
}

int main(int argc, char const *argv[])
{
	Tree T;
	int **Buffer;
	int* ColumnSizes;
	int ReturnSize;
	int i, j;

	T = CreateTree();

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	Buffer = pathSum(T, 1, &ColumnSizes, &ReturnSize);
	for (i = 0; i < ReturnSize; ++i)
	{
		for (j = 0; j < ColumnSizes[i]; ++j)
			printf("%d ", Buffer[i][j]);		
		printf("\n");
	}

	return 0;
}