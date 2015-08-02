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

int GetDepth(Tree T)
{
  int Depth = 0;

  while (T != NULL)
  {
    T = T -> left;
    ++Depth;
  }

  return Depth;
}

int Pow(int x, int y)
{
  if (y == 1)
    return x;

  if (y == 0)
    return 1;

  int Value;

  Value = Pow(x, y / 2);

  if (y % 2 == 1)
    return Value * Value * x;
  else
    return Value * Value;
}

int countNodes(struct TreeNode* root) {
  if (root == NULL)
    return 0;

  if (root -> left == 0 && root -> right == 0)
    return 1;

  int RightDepth, LeftDepth;

  LeftDepth = GetDepth(root -> left);
  RightDepth = GetDepth(root -> right);

  if (LeftDepth == RightDepth)
    return Pow(2, LeftDepth) + countNodes(root -> right);
  else
    return Pow(2, RightDepth) + countNodes(root -> left);
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


  printf("%d\n", countNodes(T));

  return 0;
}