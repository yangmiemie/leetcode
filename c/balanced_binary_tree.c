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

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

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

int isBalanced(struct TreeNode* root) {
	if (root == NULL)
		return 1;

	int LeftHeight, RightHeight;
	int rootBalanced, leftBalanced, rightBalanced;

	LeftHeight = Height(root -> left);
	RightHeight = Height(root -> right);

	rootBalanced = Abs(LeftHeight - RightHeight) > 1 ? 0 : 1;
	leftBalanced = isBalanced(root -> left);
	rightBalanced = isBalanced(root -> right);

	return rootBalanced && leftBalanced && rightBalanced;
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

void PostOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	PostOrderTraverse(T -> left);
	PostOrderTraverse(T -> right);
	printf("%d ", T -> val);
}


void InOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	InOrderTraverse(T -> left);
	printf("%d ", T -> val);
	InOrderTraverse(T -> right);
}

void PreOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	printf("%d ", T -> val);
	PreOrderTraverse(T -> left);
	PreOrderTraverse(T -> right);
}

int main(int argc, char const *argv[])
{
	int array[] = {7, 3, 8};
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