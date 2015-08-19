// Remove all elements from a linked list of integers that have value val.

// Example
// Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
// Return: 1 --> 2 --> 3 --> 4 --> 5

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

#include "lib/list.h"

typedef struct ListNode* Position;
typedef struct ListNode* List;

struct ListNode* removeElements(struct ListNode* head, int val) {
  if (head == NULL)
    return NULL;

  Position P, P1;

  P = head;
  while (P != NULL && P -> val == val)
    P = P -> next;

  head = P;
  while (P != NULL)
  {
    for (P1 = P -> next; P1 != NULL && P1 -> val == val; P1 = P1 -> next);
    P -> next = P1;
    P = P -> next;
  }

  return head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

  L1 = CreateEvenList(1);
  L2 = CreateIdenticalList(10);
  L = NewListNode(10);
  L -> next = L2;
  PrintList(L1);
  PrintList(L2);
  PrintList(L);

  L = removeElements(L, 0);
  PrintList(L);
  return 0;
}