#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#define Position struct ListNode* 
#define List struct ListNode* 

Position NewListNode(int Value)
{
  Position P;

  P = malloc(sizeof(struct ListNode));
  P -> val = Value;
  P -> next = NULL;

  return P;
}

void PrintList(List L)
{
  while (L != NULL)
  {
    printf("%d ", L -> val);
    L = L -> next;
  }

  printf("\n");
}

List CreateList(int Size)
{
  List L, *P;
  int i;

  L = NewListNode(0);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    P -> next = NewListNode(i);
    P = P -> next;    
  }

  return L;
}

List CreateDupList(int Size)
{
  List L, *P;
  int i, j;

  L = NewListNode(0);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    for (j = 0; j < i / 2; ++j)
    {
      P -> next = NewListNode(i);
      P = P -> next; 
    }   
  }

  return L;
}

List CreateRandList(int Size)
{
  List L, *P;
  int i;

  L = NewListNode(0);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    P -> next = NewListNode(rand() % (Size * 4));
    P = P -> next;    
  }

  return L;
}

List CreateReversedList(int Size)
{
  List L, *P;
  int i;

  L = NewListNode(Size);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    P -> next = NewListNode(Size - i);
    P = P -> next;    
  }

  return L;
}


List CreateOddList(int Size)
{
  List L, *P;
  int i;

  L = NewListNode(1);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    P -> next = NewListNode(2 * i + 1);
    P = P -> next;    
  }

  return L;
}

List CreateEvenList(int Size)
{
  List L, *P;
  int i;

  L = NewListNode(0);
  P = L;
  for (i = 1; i <= Size; ++i)
  {
    P -> next = NewListNode(2 * i);
    P = P -> next;    
  }

  return L;
}

Position Find(List L, int Value)
{
  while (L != NULL)
  {
    if (L -> val == Value)
      return L;

    L = L -> next;
  }

  return NULL;
}

void DestroyList(List L)
{
  List P;

  while (L != NULL)
  {
    P = L;
    L = L -> next;
    free(P);
  }
}

#undef Position
#undef List