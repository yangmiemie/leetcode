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

#define ElementType Position

struct StackRecord
{
  int Size;
  int Capacity;
  ElementType* Next;
};

typedef struct StackRecord* Stack;
#define SIZE 2

Stack Initialize()
{
  Stack S;

  S = malloc(sizeof(struct StackRecord));
  S -> Size = 0;
  S -> Capacity = SIZE;
  S -> Next = malloc(sizeof(ElementType) * S -> Capacity);

  return S;
}

int IsEmpty(Stack S)
{
  return S -> Size == 0;
}

int IsFull(Stack S)
{
  return S -> Capacity == S -> Size;
}

ElementType Pop(Stack S)
{
  if (IsEmpty(S))
  {
    fprintf(stderr, "Empty Stack\n");
    exit(1);
  }

  return S -> Next[--S -> Size];
}

void Push(Stack S, ElementType X)
{
  if (IsFull(S))
  {
    S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
    S -> Capacity *= 2;
  }

  S -> Next[S -> Size++] = X;
}

void Destroy(Stack S)
{
  free(S -> Next);
  free(S);
}

int kthSmallest(struct TreeNode* root, int k) {
  Stack S;
  Position Node;
  int i;

  if (root == NULL)
    return 0;

  S = Initialize();
  Node = root;
  i = 0;
  while (Node != NULL || !IsEmpty(S))
  {
    if (Node != NULL)
    {
      Push(S, Node);
      Node = Node -> left;      
    }
    else
    {
      Node = Pop(S);

      if (++i == k)
        break;
      // printf("%d ", Node -> val);

      if (Node -> right)
        Node = Node -> right;
      else
        Node = NULL;
    }
  }

  return Node -> val;
}

int main(int argc, char const *argv[])
{
  Tree T;
  int Value;

  T = CreateTree();

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  Value = kthSmallest(T, 4);
  printf("Value = %d\n", Value);
  return 0;
}