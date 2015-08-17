// Sort a linked list using insertion sort.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>

#include "lib/list.h"

typedef struct ListNode* Position;
typedef struct ListNode* List;

void Swap(Position P1, Position P2)
{
  int Temp;

  Temp = P1 -> val;
  P1 -> val = P2 -> val;
  P2 -> val = Temp;
}

struct ListNode* insertionSortList(struct ListNode* head) {
  if (head == NULL)
    return NULL;

  Position P1, P2, PtrNode;

  P1 = head -> next;
  P2 = head;
  while (P1 != NULL)
  {
    if (P1 -> val < P2 -> val)
    {
      PtrNode = head;
      while (PtrNode -> val < P1 -> val && PtrNode != P1)
        PtrNode = PtrNode -> next;

      if (PtrNode != P1)
      {
        P2 -> next = P1 -> next;
        Swap(P1, PtrNode);
        P1 -> next = PtrNode -> next;
        PtrNode -> next = P1;
      }
    }

    P2 = P1;
    P1 = P1 -> next;
  }

  return head;
}

int main(int argc, char const *argv[])
{
  List L;
  
  L = CreateRandList(16);
  PrintList(L);

  L = insertionSortList(L);
  PrintList(L);
  DestroyList(L);

  L = CreateReversedList(16);
  PrintList(L);

  L = insertionSortList(L);
  PrintList(L);
  DestroyList(L);

  L = CreateList(16);
  PrintList(L);

  L = insertionSortList(L);
  PrintList(L);
  DestroyList(L);

  return 0;
}