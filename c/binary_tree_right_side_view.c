/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

struct RSTreeNode 
{
  Position P;
  int Level;
};

typedef struct RSTreeNode* RSTree;
typedef struct RSTreeNode* RSPosition;

#define ElementType RSPosition
#define SIZE 8

struct QueueRecord
{
  int Front;
  int Rear;
  int Capacity;
  ElementType* Next;
};

typedef struct QueueRecord* Queue;

struct ArrayRecord
{
  int Size;
  int Capacity;
  int* Buffer;
};

typedef struct ArrayRecord* Array;

Queue Initialize()
{
  Queue Q;

  Q = malloc(sizeof(struct QueueRecord));
  Q -> Rear = Q -> Front = 0;
  Q -> Capacity = SIZE;
  Q -> Next = malloc(sizeof(ElementType) * SIZE);

  return Q;
}

int Succ(Queue Q, int Index)
{
  if (++Index >= Q -> Capacity)
    return Index % Q -> Capacity;

  return Index;
}

int isFull(Queue Q)
{
  return Succ(Q, Q -> Front) == Q -> Rear;
}

int isEmpty(Queue Q)
{
  return Q -> Front == Q -> Rear;
}

ElementType Dequeue(Queue Q)
{
  int i;

  if (isEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  i = Q -> Rear;
  Q -> Rear = Succ(Q, Q -> Rear);
  return Q -> Next[i];
}


Queue Rearrange(Queue Q)
{
  ElementType *Buffer;
  int i;

  Buffer = malloc(Q -> Capacity * 2 * sizeof(ElementType));

  i = 0;
  while (!isEmpty(Q))
    Buffer[i++] = Dequeue(Q);

  free(Q -> Next);
  Q -> Next = Buffer;
  Q -> Capacity *= 2;
  Q -> Front = i - 1;
  Q -> Rear = 0;
  return Q;
}

void Enqueue(Queue Q, ElementType X)
{
  if (isFull(Q))
    Q = Rearrange(Q);

  Q -> Next[Q -> Front] = X;
  Q -> Front = Succ(Q, Q -> Front);
}

ElementType Rear(Queue Q)
{
  if (isEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  return Q -> Next[Q -> Rear];
}

void Destroy(Queue Q)
{
  free(Q -> Next);
  free(Q);
}

RSPosition NewRSNode(Position P, int L)
{
  RSPosition RSP;

  RSP = malloc(sizeof(struct RSTreeNode));
  RSP -> P = P;
  RSP -> Level = L;

  return RSP;
}

void FreeRSNode(RSPosition RSP)
{
  free(RSP -> P);
  free(RSP);
}

Array InitializeArray()
{
  Array A;

  A = malloc(sizeof(struct ArrayRecord));
  A -> Size = 0;
  A -> Capacity = SIZE;
  A -> Buffer = malloc(sizeof(int) * SIZE);

  return A;
}

void PushToArray(Array A, int Value)
{
  if (A -> Size == A -> Capacity)
  {
    A -> Buffer = realloc(A -> Buffer, A -> Capacity * 2 * sizeof(int));
    A -> Capacity *= 2;
  }

  A -> Buffer[A -> Size++] = Value;
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    Queue Q;
    RSPosition RSP, TopNode;
    Array A;

    if (root == NULL)
    {
      *returnSize = 0;
      return NULL;
    }

    Q = Initialize();
    Enqueue(Q, NewRSNode(root, 0));
    A = InitializeArray();
    while (!isEmpty(Q))
    {
      RSP = Dequeue(Q);

      // PushToArray(A, RSP -> P -> val);

      if (isEmpty(Q))
      {
        PushToArray(A, RSP -> P -> val);
      }
      else
      {
        TopNode = Rear(Q);
        if (RSP -> Level < TopNode -> Level)
          PushToArray(A, RSP -> P -> val);
      }

      if (RSP -> P -> left)
        Enqueue(Q, NewRSNode(RSP -> P -> left, RSP -> Level + 1));

      if (RSP -> P -> right)
        Enqueue(Q, NewRSNode(RSP -> P -> right, RSP -> Level + 1));

      FreeRSNode(RSP);
    }

    Destroy(Q);
    
    *returnSize = A -> Size;
    return A -> Buffer;
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
  // Len = 100;
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
  int i, returnSize;
  int* Buffer;
  Queue Q;

  T = CreateTree();
  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");
  
  PostOrderTraverse(T);
  printf("\n");
  // MakeEmpty(T);


  // Q = Initialize();
  // for (i = 0; i < 80; ++i)
  //   Enqueue(Q, i);

  // while (!isEmpty(Q))
  //   printf("%d ", Dequeue(Q));
  // printf("\n");
  // T = NULL;
  Buffer = rightSideView(T, &returnSize);
  
  printf("%d\n", returnSize);
  for (i = 0; i < returnSize; ++i)
    printf("%d ", Buffer[i]);
  free(Buffer);
  printf("\n");

  // MakeEmpty(T);
  return 0;
}