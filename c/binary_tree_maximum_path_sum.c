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
#include <limits.h>

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int Max3(int a, int b, int c)
{
	int x;
	x = a > b ? a : b;
	x = x > c ? x : c;
	return x;
}

int maxTreePathSum(struct TreeNode* root, int* MaxPathSum)
{
  if (root == NULL)
  	return 0;

  if (root -> left == NULL && root -> right == NULL)
  {
	  if (root -> val > *MaxPathSum)
	  	*MaxPathSum = root -> val;

  	return root -> val;  	
  }

  int LeftMaxPathSum, RightMaxPathSum, Tmp;

  LeftMaxPathSum = maxTreePathSum(root -> left, MaxPathSum);
  RightMaxPathSum = maxTreePathSum(root -> right, MaxPathSum);

  if (LeftMaxPathSum > 0 && (LeftMaxPathSum + root -> val > *MaxPathSum))
  	*MaxPathSum = LeftMaxPathSum + root -> val;

  if (RightMaxPathSum > 0 && (RightMaxPathSum + root -> val) > *MaxPathSum)
  	*MaxPathSum = RightMaxPathSum + root -> val;

  if (root -> val > *MaxPathSum)
  	*MaxPathSum = root -> val;

  if (LeftMaxPathSum > 0 && RightMaxPathSum > 0 && (RightMaxPathSum + LeftMaxPathSum + root -> val) > *MaxPathSum)
  	*MaxPathSum = RightMaxPathSum + LeftMaxPathSum + root -> val;

  return Max3(LeftMaxPathSum + root -> val, RightMaxPathSum + root -> val, root -> val);
}

int maxPathSum(struct TreeNode* root) {
	int MaxPathSum = INT_MIN;
	maxTreePathSum(root, &MaxPathSum);
	return MaxPathSum;
}

int main(int argc, char const *argv[])
{
	Tree T;
	int MaxPathSum;

	T = CreateTree();

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	MaxPathSum = maxPathSum(T);
	printf("%d\n", MaxPathSum);

	return 0;
}