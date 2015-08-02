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

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL)
      return NULL;

    Tree T;

    T = root -> right;
    root -> right = root -> left;
    root -> left = T;

    invertTree(root -> left);
    invertTree(root -> right);

    return root;
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

  T = invertTree(T);

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  return 0;
}