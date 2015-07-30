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

Tree NewNode(int value)
{
  Tree T;
  T = malloc(sizeof(struct TreeNode));
  T -> val = value;
  T -> left = T -> right = NULL;
  return T;
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
  int Array[] = {8, 6, 4, 7, 10, 9, 12};;

  T = NULL;
  Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 0;
  for (i = 0; i < Len; ++i)
    T = Insert(Array[i], T);
    // T = Insert(rand() % 1024, T);

  return T;
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