// Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

#include <stdio.h>
#include <stdlib.h>

#include "lib/list.h"

#define ElementType int
#define Prime 17

typedef struct ListNode* List;
typedef struct ListNode* Position;
typedef struct HashTbl* HashTable;

struct HashTbl
{
  int TableSize;
  List* TheLists;
};

Position NewListNode(int Value)
{
  Position P;

  P = malloc(sizeof(struct ListNode));
  P -> val = Value;
  P -> next = NULL;

  return P;
}

HashTable Initialize(int Capacity)
{
  HashTable HT;
  int i;

  HT = malloc(sizeof(struct HashTbl));
  HT -> TableSize = Capacity;
  HT -> TheLists = malloc(sizeof(Position) * Capacity);

  for (i = 0; i < Capacity; ++i)
  {
    HT -> TheLists[i] = NewListNode(-1);
  }

  return HT;
}

int Hash(int Value)
{
  while (Value < 0)
    Value += Prime;

  return Value % Prime;
}

// Position Find(HashTable HT, int Value)
// {
//  List L;
//  Position P;

//  L = HT -> TheLists[Hash(Value)];

//  P = L -> next;

//  for (; P != NULL; P = P -> next)
//  {
//    if (P -> val == Value)
//      return P;
//  }

//  return NULL;
// }

void Insert(HashTable HT, int Value)
{
  List L;
  Position P;

  L = HT -> TheLists[Hash(Value)];

  P = L -> next;

  for (; P != NULL; P = P -> next)
  {
    if (P -> val == Value)
      return;
  }
  
  P = NewListNode(Value);
  P -> next = L -> next;
  L -> next = P;  
}

int FindAndInsert(HashTable HT, int Value)
{
  List L;
  Position P;

  L = HT -> TheLists[Hash(Value)];

  P = L -> next;

  for (; P != NULL; P = P -> next)
  {
    if (P -> val == Value)
      return 1;
  }
  
  P = NewListNode(Value);
  P -> next = L -> next;
  L -> next = P;  
  return 0;
}

int containsDuplicate(int* nums, int numsSize) {
  if (nums == NULL || numsSize <= 1)
    return 0;

  int i;
  HashTable HT;

  HT = Initialize(Prime);
  for (i = 0; i < numsSize; ++i)
  {
    if (FindAndInsert(HT, nums[i]) == 1)
      return 1;
  }

  return 0;
}

int main(int argc, char const *argv[])
{
  int* Numbers;
  int Len, i;

  Len = 10;
  Numbers = malloc(sizeof(int) * Len);
  Numbers[0] = -100;

  for (i = 1; i < Len; ++i)
    Numbers[i] = i;

  printf("%d\n", containsDuplicate(Numbers, Len));
  return 0;
}