/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
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

struct LevelTreeNode
{
  Position Node;
  int Level;
};

typedef struct LevelTreeNode* LevelTree;
typedef struct LevelTreeNode* LevelPosition;

LevelPosition NewLevelNode(Position P, int Level)
{
  LevelPosition LP;

  LP = malloc(sizeof(struct LevelTreeNode));
  LP -> Node = P;
  LP -> Level = Level;

  return LP;
}

#define ElementType LevelPosition
#define SIZE 2

struct QueueRecord
{
  int Front;
  int Rear;
  int Capacity;
  ElementType* Next;
};

typedef struct QueueRecord* Queue;

Queue InitializeQueue()
{
  Queue Q;

  Q = malloc(sizeof(struct QueueRecord));
  Q -> Front = Q -> Rear = 0;
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

int IsQueueEmpty(Queue Q)
{
  return Q -> Front == Q -> Rear;
}

int IsQueueFul(Queue Q)
{
  return Succ(Q, Q -> Rear) == Q -> Front;
}

ElementType Dequeue(Queue Q)
{
  if (IsQueueEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  int i;
  i = Q -> Front;
  Q -> Front = Succ(Q, Q -> Front);
  return Q -> Next[i];
}

Queue Rearrange(Queue Q)
{
  ElementType* Buffer;
  int i;

  Buffer = malloc(sizeof(ElementType) * Q -> Capacity * 2);
  i = 0;
  while (!IsQueueEmpty(Q))
    Buffer[i++] = Dequeue(Q);

  Q -> Capacity *= 2;
  Q -> Front = 0;
  Q -> Rear = i;
  free(Q -> Next);
  Q -> Next = Buffer;

  return Q;
}

void Enqueue(Queue Q, ElementType X)
{
  if (IsQueueFul(Q))
    Q = Rearrange(Q);

  Q -> Next[Q -> Rear] = X;
  Q -> Rear = Succ(Q, Q -> Rear);
}

ElementType Front(Queue Q)
{
  if (IsQueueEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);    
  }

  return Q -> Next[Q -> Front];
}

struct ReturnValueRecord
{
  int X;
  int Y;
  int** Buffer;
  int* ColumnSizes;
  int* ColumnCapacity;
  int Capacity;
};

typedef struct ReturnValueRecord* RetValue;

RetValue InitializeRetValue()
{
  RetValue RV;
  int i;

  RV = malloc(sizeof(struct ReturnValueRecord));
  RV -> X = RV -> Y = 0;
  RV -> Capacity = SIZE;
  RV -> ColumnSizes = malloc(sizeof(int) * SIZE);
  RV -> ColumnCapacity = malloc(sizeof(int) * SIZE);
  for (i = 0; i < SIZE; ++i)
  {
    RV -> ColumnCapacity[i] = SIZE;
    RV -> ColumnSizes[i] = 0;
  } 

  RV -> Buffer = malloc(sizeof(int*) * SIZE);

  for (i = 0; i < SIZE; ++i)
    RV -> Buffer[i] = malloc(sizeof(int) * SIZE);

  return RV;
}

void PushToRetValue(RetValue RV, int Value)
{
  int i;

  if (RV -> Y >= RV -> Capacity)
  {
    RV -> ColumnSizes = realloc(RV -> ColumnSizes, RV -> Capacity * 2 * sizeof(int));
    RV -> ColumnCapacity = realloc(RV -> ColumnCapacity, RV -> Capacity * 2 * sizeof(int));
    RV -> Buffer = realloc(RV -> Buffer, RV -> Capacity * 2 * sizeof(int*));

    for (i = RV -> Y; i < RV -> Capacity * 2; ++i)
    {
      RV -> ColumnSizes[i] = 0;
      RV -> Buffer[i] = malloc(sizeof(int) * SIZE);
      RV -> ColumnCapacity[i] = SIZE;
    } 
  
    RV -> Capacity *= 2;
  }

  if (RV -> X >= RV -> ColumnCapacity[RV -> Y])
  {
    RV -> Buffer[RV -> Y] = realloc(RV -> Buffer[RV -> Y], sizeof(int) * RV -> ColumnCapacity[RV -> Y] * 2);
    RV -> ColumnCapacity[RV -> Y] *= 2;
  }

  (RV -> Buffer)[RV -> Y][RV -> X] = Value;
  ++ RV -> X;
  ++ RV -> ColumnSizes[RV -> Y];
}

void Reverse(int* Array, int Size)
{
  int i, j, Temp;

  i = 0;
  j = Size - 1;

  while (i < j)
  {
    Temp = Array[i];
    Array[i] = Array[j];
    Array[j] = Temp;

    ++i;
    --j;
  }
}

int** zigzagLevelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
  RetValue RV;
  Queue Q;
  LevelPosition LP, FrontNode;

  if (root == NULL)
  {
    *columnSizes = 0;
    returnSize = 0;
    return NULL;
  }

  RV = InitializeRetValue();
  Q = InitializeQueue();
  Enqueue(Q, NewLevelNode(root, 0));

  while (!IsQueueEmpty(Q))
  {
    LP = Dequeue(Q);

    if (LP -> Node -> left)
      Enqueue(Q, NewLevelNode(LP -> Node -> left, LP -> Level + 1));
    if (LP -> Node -> right)
      Enqueue(Q, NewLevelNode(LP -> Node -> right, LP -> Level + 1));

    PushToRetValue(RV, LP -> Node -> val);


    if (IsQueueEmpty(Q) || LP -> Level != Front(Q) -> Level)
    {
      if (LP -> Level % 2 == 1)
      {
        Reverse(RV -> Buffer[RV -> Y], RV -> ColumnSizes[RV -> Y]);
      }

      ++ RV -> Y;
      RV -> X = 0;
    }
  }

  *columnSizes = RV -> ColumnSizes;
  *returnSize = RV -> Y;
  return RV -> Buffer;
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

int main(int argc, char const *argv[])
{
  Tree T;
  int ReturnSize;
  int *ColumnSizes;
  int** Buffer;
  int i, j;

  T = CreateTree();

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  Buffer = zigzagLevelOrder(T, &ColumnSizes, &ReturnSize);

  printf("ReturnSize = %d\n", ReturnSize);

  for (i = 0; i < ReturnSize; ++i)
    printf("%d ", ColumnSizes[i]);
  printf("\n");

  for (i = 0; i < ReturnSize; ++i)
  {
    for (j = 0; j < ColumnSizes[i]; ++j)
      printf("%d ", Buffer[i][j]);
    printf("\n");
  }
  return 0;
}

