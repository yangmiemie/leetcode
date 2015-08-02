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

int maxDepth(struct TreeNode* root) {
	if (root == NULL)
		return 0;

	if (root -> left == NULL && root -> right == NULL)
		return 1;

	int leftDepth, rightDepth;

	leftDepth = maxDepth(root -> left);
	rightDepth = maxDepth(root -> right);

	return Max(leftDepth, rightDepth) + 1;
}

int main(int argc, char const *argv[])
{
	Tree T;
	int Depth;

	T = CreateTree();

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	Depth = maxDepth(T);
	printf("%d\n", Depth);
	return 0;
}