// Given a binary tree

//     struct TreeLinkNode {
//       TreeLinkNode *left;
//       TreeLinkNode *right;
//       TreeLinkNode *next;
//     }
// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

// Initially, all next pointers are set to NULL.

// Note:

// You may only use constant extra space.
// You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
// For example,
// Given the following perfect binary tree,
//          1
//        /  \
//       2    3
//      / \  / \
//     4  5  6  7
// After calling your function, the tree should look like:
//          1 -> NULL
//        /  \
//       2 -> 3 -> NULL
//      / \  / \
//     4->5->6->7 -> NULL

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  struct TreeLinkNode *left, *right, *next;
 * };
 *
 */

#include <stdio.h>

#include "lib/tree.h"

// struct TreeNode {
//   int val;
//   struct TreeNode* left, *right, *next;
// };

typedef struct TreeNode* Position;
typedef struct TreeNode* Tree;

void connect(struct TreeNode *root) {
  if (root == NULL)
    return;

  Position P1, P2;
  Position PtrStart;

  P1 = P2 = NULL;
  P1 = root;
  P1 -> next = NULL;
  PtrStart = P1 -> left;

  while (P1 != NULL && P1 -> left != NULL)
  {
    P1 -> left -> next = P1 -> right;

    if (P1 -> next == NULL)
    {
      P1 -> right -> next = NULL;
      P1 = PtrStart;
      PtrStart = P1 -> left;
    }
    else
    {
      P2 = P1;
      P1 = P1 -> next;
      P2 -> right -> next = P1 -> left;
    }
  }
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

  connect(T);
  return 0;
}