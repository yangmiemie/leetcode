// Given a linked list, swap every two adjacent nodes and return its head.

// For example,
// Given 1->2->3->4, you should return the list as 2->1->4->3.

// Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.


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

struct ListNode* swapPairs(struct ListNode* head) {
	if (head == NULL || head -> next == NULL)
		return head;

	Position P1, P2, P3;
	P1 = head;
	head = head -> next;
	P2 = head -> next;
	head -> next = P1;
	P1 -> next = P2;

	while (P2 != NULL && P2 -> next != NULL)
	{
		P3 = P2 -> next;
		P2 -> next = P3 -> next;
		P1 -> next = P3;
		P3 -> next = P2;

		P1 = P2;
		P2 = P1 -> next;
	}

	return head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

	L1 = CreateEvenList(1);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  L1 = swapPairs(L1);
  PrintList(L1);

  L2 = swapPairs(L2);
  PrintList(L2);
	return 0;
}