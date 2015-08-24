// Write a program to find the n-th ugly number.

// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

// Note that 1 is typically treated as an ugly number.

#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define FIVE 5
#define TWO 2
#define THREE 3

typedef struct ListNode* Position;
typedef struct ListRecord* List;
typedef struct Item* PtrItem;

struct ListRecord
{
  Position Head;
  Position Last;
};

struct ListNode
{
  ElementType val;
  Position next;
};

struct Item
{
  Position P;
};

List Initialize()
{
  List L;

  L = malloc(sizeof(struct ListRecord));
  L -> Head = L -> Last = NULL;

  return L;
}

Position NewListNode(int Value)
{
  Position P;

  P = malloc(sizeof(struct ListNode));
  P -> next = NULL;
  P -> val = Value;
  return P;
}

void Insert(List L, int Value)
{
  if (L -> Head == NULL)
  {
    L -> Head = NewListNode(Value);
    L -> Last = L -> Head;
    return;
  }

  L -> Last -> next = NewListNode(Value);
  L -> Last = L -> Last -> next;
}

void Destroy(List L)
{
  Position P1, P2;

  for (P1 = L -> Head; P1 != NULL; )
  {
    P2 = P1 -> next;
    free(P1);
    P1 = P2;
  }

  free(L);
}

int GetMinOfThreeNum(PtrItem P1, PtrItem P2, PtrItem P3, PtrItem* TargetItem)
{
  int a, b, c;

  a = P1 -> P -> val * TWO;
  b = P2 -> P -> val * THREE;
  c = P3 -> P -> val * FIVE;

  if (a > b)
  {
    if (b < c)
    {
      *TargetItem = P2;
      return b;
    }
    else
    {
      *TargetItem = P3;           
      return c;
    }
  }
  else
  {
    if (a < c)
    {
      *TargetItem = P1;                 
      return a;
    }
    else
    {
      *TargetItem = P3;           
      return c;
    } 
  }
}

PtrItem NewItem()
{
  PtrItem Ptr;

  Ptr = malloc(sizeof(struct Item));
  Ptr -> P = NULL;

  return Ptr;
}

int nthUglyNumber(int n) {
  List L;
  PtrItem TwoItem, ThreeItem, FiveItem, TargetItem;
  Position P;
  int i, NextUglyNumber;

  TwoItem = NewItem();
  ThreeItem = NewItem();
  FiveItem = NewItem();

  L = Initialize();
  Insert(L, 1);
  TwoItem -> P = ThreeItem -> P = FiveItem -> P = L -> Head;

  i = 1;
  while (i < n)
  {
    NextUglyNumber = GetMinOfThreeNum(TwoItem, ThreeItem, FiveItem, &TargetItem);
    if (NextUglyNumber != L -> Last -> val)
    {
      Insert(L, NextUglyNumber);
      ++i;
    }
  
    TargetItem -> P = TargetItem -> P -> next;    
  }

  NextUglyNumber = L -> Last -> val;;
  Destroy(L);
  return NextUglyNumber;
}

// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 
int main(int argc, char const *argv[])
{
  int i, n;

  // n = atoi(argv[1]);
  n = 10;
  for (i = 1; i <= n; ++i)
    printf("%d ", nthUglyNumber(i));

  printf("\n");
  return 0;
}