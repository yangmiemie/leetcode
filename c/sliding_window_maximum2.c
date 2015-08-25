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

#define ElementType int
#define MAX 2

typedef struct QueueRecord* Queue;
typedef struct ResultRecord* Result;

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

int Prev(Queue Q, int Index)
{
  if (--Index < 0)
    return Index + Q -> Capacity;

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

ElementType PopBack(Queue Q)
{
  if (IsEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  int Index;

  Index = Q -> Rear - 1;
  Q -> Rear = Prev(Q, Q -> Rear);
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

ElementType Front(Queue Q)
{
  if (IsEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  return Q -> Next[Q -> Front];
}

ElementType Rear(Queue Q)
{
  if (IsEmpty(Q))
  {
    fprintf(stderr, "Empty Queue\n");
    exit(1);
  }

  return Q -> Next[Prev(Q, Q -> Rear)];
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

// int Numbers[] = {9,10,9,-7,-4,-8,2,-6};
int* maxSlidingWindow (int* nums, int numsSize, int k, int* returnSize) {
  Queue Q;
  Result R;
  int i;

  if (nums == NULL || numsSize == 0)
    return NULL;

  Q = Initialize(MAX);
  R = InitializeResult(MAX);

  for (i = 0; i < k; ++i)
  {
    while (!IsEmpty(Q) && nums[Rear(Q)] < nums[i])
      PopBack(Q);

    Enqueue(Q, i);
  }

  for (i = k; i < numsSize; ++i)
  {
    AddToResult(R, nums[Front(Q)]);
    if (Front(Q) <= i - k)
      Dequeue(Q);

    while (!IsEmpty(Q) && nums[Rear(Q)] <= nums[i])
      PopBack(Q);

    Enqueue(Q, i);
  }

  AddToResult(R, nums[Front(Q)]);
  Destroy(Q);

  *returnSize = R -> Size;
  return R -> Next;
}

int main(int argc, char const *argv[])
{
  // TestQueue();
  // int Numbers[] = {2, 4, 7};
  // int Numbers[] = {1, 3, -1, -3, 5, 3, 6, 7};
  int Numbers[] = {9,10,9,-7,-4,-8,2,-6};
  int Len, i, k, ReturnSize;
  int *Result;

  Len = sizeof(Numbers) / sizeof(Numbers[0]);
  k = 3;
  Result = maxSlidingWindow(Numbers, Len, k, &ReturnSize);
  printf("%d\n", ReturnSize);
  for (i = 0; i < ReturnSize; ++i)
    printf("%d ", Result[i]);
  printf("\n");
  return 0;
}