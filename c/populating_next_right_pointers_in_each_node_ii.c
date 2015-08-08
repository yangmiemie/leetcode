// Follow up for problem "Populating Next Right Pointers in Each Node".

// What if the given tree could be any binary tree? Would your previous solution still work?

// Note:

// You may only use constant extra space.
// For example,
// Given the following binary tree,
//          1
//        /  \
//       2    3
//      / \    \
//     4   5    7
// After calling your function, the tree should look like:
//          1 -> NULL
//        /  \
//       2 -> 3 -> NULL
//      / \    \
//     4-> 5 -> 7 -> NULL

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

  Position P, P1, P2, PtrStart;
  P = root;
  P1 = P2 = PtrStart = NULL;
  P -> next = NULL;

  while (P != NULL)
  {
    if (P -> left != NULL)
    {
      if (PtrStart == NULL)
        PtrStart = P -> left;

      if (P2 != NULL)
      {
        P2 -> next = P -> left;
        P2 = P2 -> next;
      }
      else
      {
        P2 = P -> left;
      }
    }

    if (P -> right != NULL)
    {
      if (PtrStart == NULL)
        PtrStart = P -> right;

      if (P2 != NULL)
      {
        P2 -> next = P -> right;
        P2 = P2 -> next;
      }
      else
      {
        P2 = P -> right;
      }
    }

    if (P -> next == NULL)
    {
      P = PtrStart;
      if (P2 != NULL)
        P2 -> next = NULL;
      PtrStart = NULL;
      P2 = NULL;
    }
    else
    {
      P = P -> next;
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