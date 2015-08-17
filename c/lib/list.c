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