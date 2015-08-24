// Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

// For example,
// Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
// Therefore, return the max sliding window as [3,3,5,5,6,7].

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

#include "lib/test_queue.h"

#define ElementType Position
#define MAX 2

typedef struct QueueRecord* Queue;
typedef struct ItemNode* Position;
typedef struct ResultRecord* Result;

struct ItemNode
{
  int Value;
  int Index;
};

struct QueueRecord
{
  int Front;
  int Rear;
  int Capacity;
  ElementType* Next;
};

Queue Initialize(int Capacity)
{
  Queue Q;

  Q = malloc(sizeof(struct QueueRecord));
  Q -> Front = Q -> Rear = 0;
  Q -> Capacity = Capacity;
  Q -> Next = malloc(sizeof(ElementType) * Capacity);
}

int Succ(Queue Q, int Index)
{
  if (++Index >= Q -> Capacity)
    return Index % Q -> Capacity;

  return Index;
}

int IsFull(Queue Q)
{
  return Succ(Q, Q -> Rear) == Q -> Front;
}

int IsEmpty(Queue Q)
{
  return Q -> Front == Q -> Rear;
}

ElementType Dequeue(Queue Q)
{
  if (IsEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  int Index;
  Index = Q -> Front;
  Q -> Front = Succ(Q, Q -> Front);
  return Q -> Next[Index];
}

void Destroy(Queue Q)
{
  free(Q -> Next);
  free(Q);
}

void Enqueue(Queue Q, ElementType Value)
{
  ElementType *Buffer;
  int i;

  if (IsFull(Q))
  {
    Buffer = malloc(sizeof(ElementType) * Q -> Capacity * 2);
    i = 0;
    while (!IsEmpty(Q))
      Buffer[i++] = Dequeue(Q);

    Q -> Front = 0;
    Q -> Rear = i;
    Q -> Capacity *= 2;
    free(Q -> Next);
    Q -> Next = Buffer;
  }

  Q -> Next[Q -> Rear] = Value;
  Q -> Rear = Succ(Q, Q -> Rear);
  return;
}

// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
// Therefore, return the max sliding window as [3,3,5,5,6,7].

Position NewItemNode(int Value, int Index)
{
  Position P;

  P = malloc(sizeof(struct ItemNode));
  P -> Index = Index;
  P -> Value = Value;
  return P;
}

void Swap(ElementType* Numbers, int i, int j)
{
  int Temp;
  Position P;

  Temp = Numbers[i] -> Index;
  Numbers[i] -> Index = Numbers[j] -> Index;
  Numbers[j] -> Index = Temp;

  P = Numbers[i];
  Numbers[i] = Numbers[j];
  Numbers[j] = P;
}

ElementType* InitHeap(int* Numbers, int Size, Queue Q)
{
  ElementType* Heap;
  ElementType Node;
  int i;

  Heap = malloc(sizeof(ElementType) * Size + 1);
  for (i = 0; i < Size; ++i)
  {
    Node = NewItemNode(Numbers[i], i + 1);
    Heap[i+1] = Node;
    Enqueue(Q, Node);
  }

  return Heap;
}

void FixDown(ElementType* Numbers,int k, int Size)
{
  int j;

  while (2 * k <= Size)
  {
    j = 2 * k;
    if (j < Size && Numbers[j] -> Value < Numbers[j+1] -> Value)
      j++;

    if (Numbers[j] -> Value > Numbers[k] -> Value)
    {
      Swap(Numbers, j, k);
      k = j;
    }
    else
      break;
  }
}

void FixUp(ElementType* Numbers, int k, int Size)
{
  while (k / 2 >= 1)
  {
    if (Numbers[k] -> Value > Numbers[k/2] -> Value)
    {
      Swap(Numbers, k, k / 2);
      k = k / 2;
    }   
    else
    {
      break;
    }
  }
}

void BuildHeap(ElementType* Numbers, int Size)
{
  int i;

  for (i = Size / 2; i >= 1; --i)
    FixDown(Numbers, i, Size);
}

struct ResultRecord
{
  int Size;
  int Capacity;
  int* Next;
};

Result InitializeResult(int Capacity)
{
  Result R;

  R = malloc(sizeof(struct ResultRecord));
  R -> Size = 0;
  R -> Capacity = Capacity;
  R -> Next = malloc(sizeof(int) * Capacity);

  return R;
}

void AddToResult(Result R, int Value)
{
  if (R -> Size == R -> Capacity)
  {
    R -> Next = realloc(R -> Next, sizeof(int) * R -> Capacity * 2);
    R -> Capacity *= 2;
  }

  R -> Next[R -> Size++] = Value;
}

void AdjustRandItemInHeap(ElementType* Heap, int k, int Size)
{
  if (k > 1 && Heap[k] -> Value > Heap[k/2] -> Value)
    FixUp(Heap, k, Size);
  else 
    FixDown(Heap, k, Size);
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  if (nums == NULL || numsSize == 0)
    return NULL;
  
  Result R;
  ElementType* Heap;
  ElementType Node;
  Queue Q;
  int i;

  Q = Initialize(MAX);
  R = InitializeResult(MAX);
  Heap = InitHeap(nums, k, Q);
  BuildHeap(Heap, k);

  for (i = k; i < numsSize; ++i)
  {
    AddToResult(R, Heap[1] -> Value);
    Node = Dequeue(Q);
    Node -> Value = nums[i];
    Enqueue(Q, Node);
    AdjustRandItemInHeap(Heap, Node -> Index, k);
  }

  AddToResult(R, Heap[1] -> Value);
  *returnSize = R -> Size;
  return R -> Next;
}

// void HeapSort(int* Numbers, int Size)
// {
//  int i;

//  BuildHeap(Numbers, Size);
//  for (i = 0; i < Size - 1; ++i)
//  {
//    Swap(Numbers, 1, Size - 1 - i);
//    FixDown(Numbers, 1, Size - 2 - i);
//  }
// }

int main(int argc, char const *argv[])
{
  // TestQueue();
  int Numbers[] = {1, 3, -1, -3, 5, 3, 6, 7};
  int Len, i, k, ReturnSize;
  int *Result;

  Len = sizeof(Numbers) / sizeof(Numbers[0]);

  // HeapSort(Numbers, Len);

  // for (i = 0; i < Len; ++i)
  //  printf("%d ", Numbers[i]);
  // printf("\n");

  // ElementType* Heap;

  // Heap = InitHeap(Numbers, Len);
  // BuildHeap(Heap, Len);

  // for (i = 1; i < Len; ++i)
  //  printf("%d ", Heap[i] -> Value);

  k = Len;
  Result = maxSlidingWindow(Numbers, Len, k, &ReturnSize);
  printf("%d\n", ReturnSize);
  for (i = 0; i < ReturnSize; ++i)
    printf("%d ", Result[i]);
  printf("\n");
  return 0;
}