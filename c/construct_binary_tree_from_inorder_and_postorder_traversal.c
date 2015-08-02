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

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
  if (inorder == NULL || postorder == NULL || inorderSize == 0 || postorderSize == 0)
    return NULL;

  if (inorderSize == 1 && postorderSize == 1 && *inorder == *postorder)
    return NewNode(*inorder);

  Tree Root;
  int* PtrRoot;
  int i;

  PtrRoot = postorder + postorderSize - 1;

  for (i = 0; i < inorderSize; ++i)
    if (inorder[i] == *PtrRoot)
      break;

  Root = NewNode(*PtrRoot);

  Root -> left = buildTree(inorder, i, postorder, i);
  Root -> right = buildTree(inorder + i + 1, inorderSize - i - 1, postorder + i, postorderSize - i - 1);

  return Root;
}

int main(int argc, char const *argv[])
{
  Tree T;
  int Postorder[] = {4, 7, 9, 12, 10, 8};
  int Inorder[] = {4, 7, 8, 9, 10, 12};

  // T = CreateTree();

  // PreOrderTraverse(T);
  // printf("\n");

  // InOrderTraverse(T);
  // printf("\n");

  // PostOrderTraverse(T);
  // printf("\n");


  T = buildTree(Inorder, sizeof(Inorder) / sizeof(Inorder[0]), Postorder, sizeof(Postorder) / sizeof(Postorder[0]));

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");
  return 0;
}