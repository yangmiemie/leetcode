// Given a linked list, determine if it has a cycle in it.

// Follow up:
// Can you solve it without using extra space?

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


int hasCycle(struct ListNode *head) {
  Position P1, P2;

  if (head == NULL)
    return 0;

  P1 = P2 = head;

  while (P1 != NULL)
  {
    P2 = P2 -> next;

    if (P1 -> next == NULL)
      return 0;

    P1 = P1 -> next -> next;

    if (P1 == P2)
      return 1;
  }

  return 0;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L3;
  Position P;

  L1 = CreateList(1);
  PrintList(L1);
  printf("%d\n", hasCycle(L1));

  for (P = L1; P -> next != NULL; P = P -> next);
  P -> next = L1;
  printf("%d\n", hasCycle(L1));

  L2 = CreateList(5);
  PrintList(L2);
  printf("%d\n", hasCycle(L2));
  for (P = L2; P -> next != NULL; P = P -> next);
  P -> next = L2;
  printf("%d\n", hasCycle(L2));

  L3 = CreateList(2);
  PrintList(L3);
  printf("%d\n", hasCycle(L3));
  for (P = L3; P -> next != NULL; P = P -> next);
  P -> next = L3;
  printf("%d\n", hasCycle(L3));
  return 0;
}