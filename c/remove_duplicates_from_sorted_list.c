// Given a sorted linked list, delete all duplicates such that each element appear only once.

// For example,
// Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.

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

struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (head == NULL)
    return NULL;

  Position P1, P2;
  int Value;

  Value = head -> val;
  P1 = head -> next;
  P2 = head;
  while (P1 != NULL)
  {
    if (P1 -> val != Value)
    {
      P2 -> next = P1;
      P2 = P2 -> next;
      Value = P1 -> val;
    } 

    P1 = P1 -> next;
  }

  P2 -> next = NULL;
  return head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

  L1 = CreateEvenList(10);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  L1 = deleteDuplicates(L1);
  L2 = deleteDuplicates(L2);

  PrintList(L1);
  PrintList(L2);

  L1 = CreateDupList(10);
  PrintList(L1);
  L1 = deleteDuplicates(L1);
  PrintList(L1);

  return 0;
}