// Write an algorithm to determine if a number is "happy".

// A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

// Example: 19 is a happy number

// 1^2 + 9^2 = 82
// 8^2 + 2^2 = 68
// 6^2 + 8^2 = 100
// 1^2 + 0^2 + 0^2 = 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ElementType int
#define Prime 17

typedef struct ListNode* Position;
typedef struct ListNode* List;
typedef struct HashTbl* HashTable;

struct ListNode
{
  ElementType val;
  Position next;
};

struct HashTbl
{
  List* TheList;
  int TableSize;
};

int Hash(int Value)
{
  return Value % Prime;
}

Position NewNode(int Value)
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
  HT -> TheList = malloc(sizeof(Position) * Capacity);

  for (i = 0; i < Capacity; ++i)
  {
    HT -> TheList[i] = NewNode(-1);
  }

  return HT;
}

Position FindAndInsert(HashTable HT, int Value)
{
  List L;
  Position P;

  L = HT -> TheList[Hash(Value)];

  for (P = L -> next; P != NULL; P = P -> next)
  {
    if (P -> val == Value)
      return P;
  }

  P = NewNode(Value);
  P -> next = L -> next;
  L -> next = P;

  return NULL;
}

void DestroyList(List L)
{
  Position P1, P2;
  P1 = L;

  while (P1 != NULL)
  {
    P2 = P1;
    P1 = P1 -> next;
    free(P2);
  }
}

void Destroy(HashTable HT)
{
  int i;

  for (i = 0; i < HT -> TableSize; ++i)
  {
    DestroyList(HT -> TheList[i]);
  }

  free(HT);
}
// Example: 19 is a happy number

// 1^2 + 9^2 = 82
// 8^2 + 2^2 = 68
// 6^2 + 8^2 = 100
// 1^2 + 0^2 + 0^2 = 1

int isHappy(int n) {
  int Sum, Result;
  HashTable HT;

  Sum = 0;
  HT = Initialize(Prime);
  Result = 1;

  while (n != 1)
  {
    if (FindAndInsert(HT, n) != NULL)
    {
      Result = 0;
      break;
    }

    Sum = 0;
    while (n > 0)
    {
      Sum += pow(n % 10, 2);
      n = n / 10;
    }

    n = Sum;
  }

  Destroy(HT);
  return Result;
}

int main(int argc, char const *argv[])
{
  int N;

  N = 32;

  printf("%d\n", isHappy(N));
  return 0;
}