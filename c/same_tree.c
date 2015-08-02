// Given two binary trees, write a function to check if they are equal or not.

// Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
	if (p == NULL && q == NULL)
		return true;

	if (p == NULL || q == NULL)
		return false;

	if (p -> val != q -> val)
		return false;

	return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);
}

int main(int argc, char const *argv[])
{
	Tree T, T2;

	T = CreateTree();
	T2 = CreateTree();

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");
		
	printf("%d\n", isSameTree(T, T2));
	return 0;
}