// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

// For example, this binary tree is symmetric:

//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// But the following is not:
//     1
//    / \
//   2   2
//    \   \
//    3    3

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

Tree InvertTree(Tree T)
{
	if (T == NULL)
		return NULL;

	if (T -> left == NULL && T -> right == NULL)
		return T;

	Tree Tmp;
	Tmp = T -> left;
	T -> left = T -> right;
	T -> right = Tmp;

	T -> left = InvertTree(T -> left);
	T -> right = InvertTree(T -> right);
	return T;
}

Tree CopyToTree(Tree T)
{
	if (T == NULL)
		return NULL;

	if (T -> left == NULL && T -> right == NULL)
		return NewNode(T -> val);

	Tree CT;
	CT = NewNode(T -> val);
	CT -> left = CopyToTree(T -> left);
	CT -> right = CopyToTree(T -> right);

	return CT;
}

bool IsSameTree(Tree T1, Tree T2)
{
	if (T1 == NULL && T2 == NULL)
		return true;

	if (T1 == NULL || T2 == NULL)
		return false;

	if (T1 -> val != T2 -> val)
		return false;

	return IsSameTree(T1 -> left, T2 -> left) && IsSameTree(T1 -> right, T2 -> right);
}

bool isSymmetric(struct TreeNode* root) {
	Tree T;
	bool IsSymmetric;
	T = CopyToTree(root);
	T = InvertTree(T);
	
	IsSymmetric = IsSameTree(root, T);
	MakeEmpty(T);

	return IsSymmetric;
}

int main(int argc, char const *argv[])
{
	Tree T, T2;

	T = CreateTree();
	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	printf("%d\n", isSymmetric(T));
	return 0;
}

