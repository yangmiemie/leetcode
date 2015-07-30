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

struct TreeNode
{
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

Tree NewNode(int value)
{
  Tree T;
  T = malloc(sizeof(struct TreeNode));
  T -> val = value;
  T -> left = T -> right = NULL;
  return T;
}

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

void PreOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  printf("%d ", T -> val);
  PreOrderTraverse(T -> left);
  PreOrderTraverse(T -> right);
}

void InOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  InOrderTraverse(T -> left);
  printf("%d ", T -> val);
  InOrderTraverse(T -> right);
}

void PostOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  PostOrderTraverse(T -> left);
  PostOrderTraverse(T -> right);
  printf("%d ", T -> val);
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