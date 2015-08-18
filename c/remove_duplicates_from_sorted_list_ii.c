// Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

// For example,
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.

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

Position FindNextDiffValue(Position P)
{
  Position Node;

  Node = P -> next;
  for (; Node != NULL && Node -> val == P -> val; Node = Node -> next);

  return Node;
}

struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (head == NULL || head -> next == NULL)
    return head;

  Position P1, P2, P;
  List Head;

  Head = NULL;
  P = NULL;
  P1 = head;

  while (P1 != NULL)
  {
    P2 = FindNextDiffValue(P1);

    if (P2 == P1 -> next)
    {
      if (Head == NULL)
      {
        Head = P1;
        P = P1;
      }
      else
      {
        P -> next = P1;
        P = P -> next;
      }
    }

    if (P2 == NULL)
    {
      if (P == NULL)
        return NULL;
      
      if (P1 -> next = NULL)
        P -> next = P1;
      else
        P -> next = NULL;
    }

    P1 = P2;
  }

  return Head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

  L1 = CreateDupList(10);
  PrintList(L1);
  L1 = deleteDuplicates(L1);
  PrintList(L1);
  
  L1 = CreateList(10);
  PrintList(L1);
  L1 = deleteDuplicates(L1);
  PrintList(L1);

  L1 = NewListNode(10);
  L1 -> next = NewListNode(10);
  PrintList(L1);
  L1 = deleteDuplicates(L1);
  // PrintList(L1);
  return 0;
}