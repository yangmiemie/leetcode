// Given a binary tree, determine if it is a valid binary search tree (BST).

// Assume a BST is defined as follows:

// The left subtree of a node contains only nodes with keys less than the node's key.
// The right subtree of a node contains only nodes with keys greater than the node's key.
// Both the left and right subtrees must also be binary search trees.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "lib/tree.h"
#include "lib/test_stack.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

#define ElementType int
#define SIZE 2

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

	S = (Stack)malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = SIZE;
	S -> Next = (ElementType*)malloc(sizeof(ElementType) * S -> Capacity);
	return S;
}

int IsFull(Stack S)
{
	return S -> Capacity == S -> Size;
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
		S -> Next = (ElementType*)realloc(S -> Next, S -> Capacity * 2 * sizeof(ElementType));
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = X;
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

void SetMaxMin(int* Value, int* MaxValue, int* MinValue)
{
	if (*Value > *MaxValue)
		*MaxValue = *Value;

	if (*Value < *MinValue)
		*MinValue = *Value;
}

bool ValidateBST(Tree T, int* MaxValue, int *MinValue)
{
	int IsLeftValid, IsRightValid;
	int LeftMaxValue, LeftMinValue, RightMaxValue, RightMinValue;

	if (T == NULL)
	{
		*MaxValue = INT_MIN;
		*MinValue = INT_MAX;		
		return true;
	}

	if (T -> left == NULL && T -> right == NULL)
	{
		SetMaxMin(&T -> val, MaxValue, MinValue);
		return true;
	}

	IsLeftValid = ValidateBST(T -> left, &LeftMaxValue, &LeftMinValue);
	IsRightValid = ValidateBST(T -> left, &RightMaxValue, &RightMinValue);

	SetMaxMin(&T -> val, MaxValue, MinValue);
	return IsLeftValid && IsRightValid && T -> val > LeftMaxValue && T -> val < RightMaxValue;
}	

void GetInOrderTraversal(Tree T, Stack S)
{
	if (T == NULL)
		return;

	GetInOrderTraversal(T -> left, S);
	Push(S, T -> val);
	GetInOrderTraversal(T -> right, S);
}

bool IsAscendantOrder(ElementType* Array, int Size)
{
	int i;

	for (i = 0; i < Size - 1; ++i)
		if (Array[i] >= Array[i+1])
			return false;

	return true;
}

bool isValidBST(struct TreeNode* root) {
	Stack S;
	bool IsValidBST;

	S = Initialize();
	GetInOrderTraversal(root, S);

	IsValidBST = IsAscendantOrder(S -> Next, S -> Size);
	Destroy(S);

	return IsValidBST;
}

int main(int argc, char const *argv[])
{
	Tree T;

	T = CreateTree();
	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	T = NULL;
	printf("%d\n", isValidBST(T));

	TestStack();
	return 0;
}