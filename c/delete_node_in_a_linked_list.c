// Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

// Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>

#include "lib/list.h"

typedef struct ListNode* Position;
typedef struct ListNode* List;

void deleteNode(struct ListNode* node) {
  Position P;

  P = node -> next;
  node -> val = P -> val;
  node -> next = P -> next;
  free(P);
}

int main(int argc, char const *argv[])
{
  List L;
  Position P;
  int i;

  L = CreateList(15);
  PrintList(L);

  for (i = 5; i < 12; ++i)
  {
    P = Find(L, i);
    deleteNode(P);
    PrintList(L);
  }

  DestroyList(L);
  
  return 0;
}