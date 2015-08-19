// Given a linked list, remove the nth node from the end of list and return its head.

// For example,

//    Given linked list: 1->2->3->4->5, and n = 2.

//    After removing the second node from the end, the linked list becomes 1->2->3->5.
// Note:
// Given n will always be valid.
// Try to do this in one pass.

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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	if (head == NULL)
		return NULL;

	Position P1, P2, P3;
	int i;

	P1 = head;
	for (i = 0; i < n; ++i)
		P1 = P1 -> next;

	P2 = head;

	while (P1 != NULL)
	{
		P3 = P2;
		P2 = P2 -> next;
		P1 = P1 -> next;
	}

	if (P2 == head)
		head = head -> next;
	else
		P3 -> next = P2 -> next;		

	return head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

	L1 = CreateEvenList(1);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  L2 = removeNthFromEnd(L2, 2);
  PrintList(L2);
	return 0;
}