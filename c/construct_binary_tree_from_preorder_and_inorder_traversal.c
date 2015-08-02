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

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
  if (preorder == NULL || preorderSize == 0 || inorder == NULL || inorderSize == 0)
    return NULL;

  if (preorderSize == 1 && inorderSize == 1 && *inorder == *preorder)
    return NewNode(*preorder);

  Tree Root;
  int* PtrRoot;
  int i;

  PtrRoot = preorder;

  for (i = 0; i < inorderSize; ++i)
    if (*PtrRoot == inorder[i])
      break;

  Root = NewNode(*PtrRoot);
  Root -> left = buildTree(preorder + 1, i, inorder, i);
  Root -> right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);

  return Root;
}

int main(int argc, char const *argv[])
{
  Tree T;
  int Preorder[] = {8, 7, 4, 10, 9, 12};
  int Inorder[] = {4, 7, 8, 9, 10, 12};

  T = buildTree(Preorder, sizeof(Preorder) / sizeof(Preorder[0]), Inorder, sizeof(Inorder) / sizeof(Inorder[0]));

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  return 0;
}