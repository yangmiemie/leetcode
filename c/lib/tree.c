#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define Tree struct TreeNode*
#define Position struct TreeNode*

Tree NewNode(int value)
{
  Tree T;
  struct TreeNode node;
  T = (Tree)malloc(sizeof(struct TreeNode));
  T -> val = value;
  T -> left = T -> right = NULL;
  T -> next = &node;
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
  int Array[] = {5, 7, 4, 6, 9, 2};;

  // T = NULL;
  // Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 0;
  // for (i = 0; i < Len; ++i)
  //   T = Insert(Array[i], T);
    // T = Insert(rand() % 1024, T);


  T = NewNode(1);
  // T -> left = NewNode(5);
  T -> right = NewNode(5);
  T -> right -> right = NewNode(7);
  T -> right -> right -> right = NewNode(17);
  T -> right -> right -> right -> right = NewNode(27);
  // T -> right -> right = NewNode(20);
  // T -> right -> left = NewNode(6);
  return T;
}

Position Find(Tree T, int Value)
{
  if (T == NULL)
    return NULL;

  if (T -> val > Value)
    return Find(T -> left, Value);
  else if (T -> val < Value)
    return Find(T -> right, Value);
  else
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

#undef Tree
#undef Position