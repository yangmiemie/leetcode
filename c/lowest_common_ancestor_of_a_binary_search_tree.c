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

#define LEFT 0
#define RIGHT 1

Tree LCA(Tree Root, Tree Left, Tree Right)
{
  if (Root == NULL)
    return NULL;

  if (Root -> val >= Left -> val && Root -> val <= Right -> val)
    return Root;
  else if (Root -> val > Right -> val)
    return LCA(Root -> left, Left, Right);
  else if (Root -> val < Left -> val)
    return LCA(Root -> right, Left, Right);
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
  if (root == NULL || p == NULL || q == NULL)
    return NULL;

  if (p -> val > q -> val)
    return LCA(root, q, p);

  return LCA(root, p, q);
}

int main(int argc, char const *argv[])
{
  Tree T;
  Position P, P1, P2;
  T = CreateTree();

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  P1 = Find(T, 10);
  P2 = Find(T, 15);
 
  P = lowestCommonAncestor(T, P2, P1);
  printf("Position = %d\n", P -> val);
  return 0;
}