// Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

// An example is the root-to-leaf path 1->2->3 which represents the number 123.

// Find the total sum of all root-to-leaf numbers.

// For example,

//     1
//    / \
//   2   3
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.

// Return the sum = 12 + 13 = 25.

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

void GetSumNumbers(Tree T, int *PathSum, int* TotalSum)
{
	if (T == NULL)
		return;

	if (T -> left == NULL && T -> right == NULL)
	{
		*TotalSum += *PathSum * 10 + T -> val;
		return;
	}

	int StoredSum;

	StoredSum = *PathSum;
	*PathSum = *PathSum * 10 + T -> val;
	GetSumNumbers(T -> left, PathSum, TotalSum);
	GetSumNumbers(T -> right, PathSum, TotalSum);

	*PathSum = StoredSum;
	return;
}

int sumNumbers(struct TreeNode* root) {
    int PathSum, TotalSum;

    PathSum = TotalSum = 0;
    GetSumNumbers(root, &PathSum, &TotalSum);
    return TotalSum;
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
	
	printf("%d\n", sumNumbers(T));
	return 0;
}