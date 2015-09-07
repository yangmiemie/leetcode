// Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
// The solution set must not contain duplicate triplets.
//     For example, given array S = {-1 0 1 2 -1 -4},

//     A solution set is:
//     (-1, 0, 1)
//     (-1, -1, 2)

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define TableSize 2
typedef struct HashTbl* HashTable;
typedef struct HTListNode* Position;
typedef struct HTListNode* List;
typedef struct ResultRecord* PtrRR;

struct HashTbl
{
  int Size;
  List* TheLists;
};

struct HTListNode
{
  ElementType Element;
  Position Next;
};

Position NewListNode(int Element)
{
  Position P;

  P = malloc(sizeof(struct HTListNode));
  P -> Element = Element;
  P -> Next = NULL;

  return P;
}

int Hash(int Value)
{
  while (Value < 0)
    Value += TableSize;

  return Value % TableSize;
}

HashTable Initialize(int Size)
{
  HashTable HT;
  int i;

  HT = malloc(sizeof(struct HashTbl));
  HT -> Size = Size;
  HT -> TheLists = malloc(sizeof(List) * Size);

  for (i = 0; i < Size; ++i)
    (HT -> TheLists)[i] = NewListNode(100);

  return HT;
} 

Position Find(HashTable HT, int Value)
{
  List L;
  Position P;

  L = (HT -> TheLists)[Hash(Value)];
  P = L -> Next;

  while (P != NULL)
  {
    if (P -> Element == Value)
      return P;
    P = P -> Next;
  }

  return NULL;
}

void Insert(HashTable HT, int Value)
{
  List L;
  Position P;

  L = (HT -> TheLists)[Hash(Value)];
  P = NewListNode(Value);

  P -> Next = L -> Next;
  L -> Next = P;
  return; 
}

void Remove(HashTable HT, int Value)
{
  List L;
  Position P1, P2;

  L = HT -> TheLists[Hash(Value)];
  P1 = L -> Next;
  P2 = L;

  while (P1 != NULL)
  {
    if (P1 -> Element == Value)
    {
      P2 -> Next = P1 -> Next;
      free(P1);
      return;
    }

    P2 = P1;
    P1 = P1 -> Next;
  }

  return; 
}

void ClearAll(HashTable HT)
{
  int i;
  Position P1, P2;

  for (i = 0; i < HT -> Size; ++i)
  {
    P1 = HT -> TheLists[i] -> Next;
    while (P1 != NULL)
    {
      P2 = P1 -> Next;
      free(P1);
      P1 = P2;
    }

    HT -> TheLists[i] -> Next = NULL;
  }
}

void Destroy(HashTable HT)
{
  int i;
  Position P1, P2;

  ClearAll(HT);

  for (i = 0; i < HT -> Size; ++i)
    free(HT -> TheLists[i]);

  free(HT -> TheLists);
  free(HT);
}

void Swap(int *Array, int i, int j)
{
  int Temp;

  Temp = Array[i];
  Array[i] = Array[j];
  Array[j] = Temp;
}

void SortArray(int *Array, int Left, int Right)
{
  int i, j;
  int Pivot;

  if (Left >= Right)
    return;

  Pivot = Array[Left];
  i = Left + 1;
  j = Right;
  while (1)
  {
    while (i < j && Array[i] < Pivot) ++i;
    while (j > Left && Array[j] >= Pivot) --j;

    if (j <= i)
      break;

    Swap(Array, i, j);
    ++i, --j;
  }

  Swap(Array, Left, j);
  SortArray(Array, Left, j - 1);
  SortArray(Array, j + 1, Right);
}

struct ResultRecord
{
  int Capacity;
  int Size;
  int** Next;
};

PtrRR InitializeRR(int Capacity)
{
  PtrRR RR;

  RR = malloc(sizeof(struct ResultRecord));
  RR -> Capacity = Capacity;
  RR -> Size = 0;
  RR -> Next =  malloc(sizeof(int*) * Capacity);

  return RR;
}

void AddValuesToRR(PtrRR RR, int V1, int V2, int V3)
{
  int i;
  for (i = 0; i < RR -> Size; ++i)
  {
    if (RR -> Next[i][0] == V1 && RR -> Next[i][1] == V2)
      return;
  }

  if (RR -> Size >= RR -> Capacity)
  {
    RR -> Next = realloc(RR -> Next, 2 * RR -> Capacity * sizeof(int*));
    RR -> Capacity *= 2;
  }

  (RR -> Next)[RR -> Size] = malloc(sizeof(int) *  3);
  (RR -> Next)[RR -> Size][0] = V1;
  (RR -> Next)[RR -> Size][1] = V2;
  (RR -> Next)[RR -> Size][2] = V3;
  RR -> Size++;
}

int** threeSum(int* nums, int numsSize, int* returnSize) {
  int i1, i2, Value;
  HashTable HT;
  Position P;
  PtrRR RR;

  SortArray(nums, 0, numsSize - 1);
  HT = Initialize(TableSize);
  RR = InitializeRR(2);

  for (i1 = 0; i1 < numsSize - 2; ++i1)
  {
    Value = 0 - nums[i1];

    for (i2 = i1 + 1; i2 < numsSize; ++i2)
    {
      if ((P = Find(HT, Value - nums[i2])) != NULL)
      {
        // AddValuesToRR(RR, nums[i1], nums[i2], nums[i2]);
        AddValuesToRR(RR, nums[i1], P -> Element, nums[i2]);
      }

      Insert(HT, nums[i2]);
    }

    ClearAll(HT);
  }

  // Destroy(HT);
  *returnSize = RR -> Size;

  return RR -> Next;
}

int main(int argc, char const *argv[])
{
  // int Numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // int Numbers[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  // int Numbers[] = {-1, -1, -1, -1, -1};
  int Numbers[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
  // int Numbers[] = {-1, 0, 1, 2, -1, -4};
  // int Numbers[] = {0, 0, 0, 0, 0};
  int i, Len;
  int ReturnSize;
  int **ReturnValue;

  Len = sizeof(Numbers) / sizeof(Numbers[0]);
  ReturnValue = threeSum(Numbers, Len, &ReturnSize);

  for (i = 0; i < ReturnSize; ++i)
    printf("%d %d %d\n", ReturnValue[i][0], ReturnValue[i][1], ReturnValue[i][2]);

  // SortArray(Numbers, 0, Len - 1);

  // for (i = 0; i < Len; ++i)
  //  printf("%d ", Numbers[i]);

  // printf("\n");


  // HashTable HT;
  // Position P;
  // HT = Initialize(TableSize);
  // for (i = 1; i < Len; ++i)
  //  Insert(HT, Numbers[i]);

  // for (i = 0; i < Len; ++i)
  // {
  //  P = Find(HT, Numbers[i]);

  //  if (P == NULL)
  //    printf("Not Found\n");
  //  else
  //    printf("%d\n", P -> Element);
  // }

  // Remove(HT, -1);
  // Remove(HT, 2);
  // Remove(HT, 3);

  // for (i = 0; i < Len; ++i)
  // {
  //  P = Find(HT, Numbers[i]);

  //  if (P == NULL)
  //    printf("Not Found\n");
  //  else
  //    printf("%d\n", P -> Element);
  // }

  // ClearAll(HT);

  // PtrRR RR;

  // RR = InitializeRR(12);
  // AddValuesToRR(RR, 1, 2, 3);
  // AddValuesToRR(RR, 2, 2, 3);
  // AddValuesToRR(RR, 3, 2, 3);
  // AddValuesToRR(RR, 4, 2, 3);

  // for (i = 0; i < RR -> Size; ++i)
  // {
  //  printf("%d %d %d\n", (RR -> Next)[i][0], RR -> Next[i][1], RR -> Next[i][2]);
  // }
  return 0;
}