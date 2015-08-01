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

// int TestStack()
// {
//  Stack S;
//  int i;

//  S = Initialize();
//  for (i = 0; i < 100; ++i)
//    Push(S, i);

//  while (!IsEmpty(S))
//    printf("%d ", Pop(S));

//  printf("\n");

//  Destroy(S);
// }

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