/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int Abs(int a)
{
	if (a < 0)
		return a * -1;

	return a;
}

int Height(Tree T)
{
	int LeftHeight, RightHeight;

	if (T == NULL)
		return 0;

	if (T -> left == NULL && T -> right == NULL)
		return 1;

	LeftHeight = Height(T -> left);
	RightHeight = Height(T -> right);

	return Max(LeftHeight, RightHeight) + 1;
}

int isTreeBalanced(Tree T, int* Height)
{
	int LeftHeight, RightHeight;
	int LeftBalanced, RightBalanced, rootBalanced;

	if (T == NULL)
	{
		*Height = 0;
		return 1;
	}

	if (T -> left == NULL && T -> right == NULL)
	{
		*Height = 1;
		return 1;
	}

	LeftBalanced = isTreeBalanced(T -> left, &LeftHeight);
	RightBalanced = isTreeBalanced(T -> right, &RightHeight);

	*Height = Max(LeftHeight, RightHeight) + 1;
	rootBalanced = Abs(LeftHeight - RightHeight) > 1 ? 0 : 1;

	return rootBalanced && LeftBalanced && RightBalanced;
}

int isBalanced(struct TreeNode* root) {
	int Height;
	return isTreeBalanced(root, &Height);
}

int main(int argc, char const *argv[])
{
	int array[] = {7, 3};
	Tree T;
	int i, Len, balanced;

	Len = sizeof(array) / sizeof(array[0]);
	T = NULL;
	for (i = 0; i < Len; ++i)
		T = Insert(array[i], T);

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	balanced = isBalanced(T);
	printf("%d\n", balanced);
	return 0;
}