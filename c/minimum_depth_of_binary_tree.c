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


int Min(int a, int b)
{
  return a > b ? b : a;
}

int minTreeDepth(struct TreeNode* root)
{
  if (root == NULL)
    return INT_MAX;

  if (root -> left == NULL && root -> right == NULL)
    return 1;

  int leftDepth, rightDepth;

  leftDepth = minTreeDepth(root -> left);
  rightDepth = minTreeDepth(root -> right);

  return Min(leftDepth, rightDepth) + 1;
}

int minDepth(struct TreeNode* root) {
  if (root == NULL)
    return 0;

  return minTreeDepth(root);
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

  Depth = minDepth(T);
  printf("%d\n", Depth);
  return 0;
}