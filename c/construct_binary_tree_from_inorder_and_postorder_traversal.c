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

Tree Insert(int value, Tree T)
{
  if (T == NULL)
    return NewNode(value);

  // T -> left = Insert(value, T -> left);
  if (T -> val > value)
    T -> left = Insert(value, T -> left);
  else if (T -> val < value)
    T -> right = Insert(value, T -> right);

  return T;
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

Tree CreateTree()
{
  Tree T;
  int Len, i;
  // int Array[] = {1, 2};
  int Array[] = {8, 7, 4, 10, 9, 12};;

  T = NULL;
  Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 0;
  for (i = 0; i < Len; ++i)
    T = Insert(Array[i], T);
    // T = Insert(rand() % 1024, T);

  return T;
}

void MakeEmpty(Tree T)
{
  if (T)
  {
    MakeEmpty(T -> left);
    MakeEmpty(T -> right);
    free(T);
  }

  return;
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