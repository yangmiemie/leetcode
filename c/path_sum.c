// Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

// For example:
// Given the below binary tree and sum = 22,
//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \      \
//         7    2      1
// return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.


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

bool hasPathSum(struct TreeNode* root, int sum) 
{
	if (root == NULL)
		return false;

	if (root -> val == sum && root -> left == NULL && root -> right == NULL)
		return true;

	return hasPathSum(root -> left, sum - root -> val) || hasPathSum(root -> right, sum - root -> val);
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

	printf("%d\n", hasPathSum(T, 0));
	return 0;
}
