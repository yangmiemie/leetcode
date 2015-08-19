// Given a list, rotate the list to the right by k places, where k is non-negative.

// For example:
// Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.

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

List ReverseList(List Head)
{
	Position P1, P2, P3;

	P1 = Head;
	P2 = Head -> next;
	P1 -> next = NULL;

	while (P2 != NULL)
	{
		P3 = P2 -> next;
		P2 -> next = P1;

		P1 = P2;
		P2 = P3;
	}

	return P1;
}

List RotateWithPosition(List head, int k)
{
	Position P1, P2, P3, P4;
	int i;

	P1 = head;
	for (i  = 0; i < k && P1 != NULL; ++i)
		P1 = P1 -> next;

	P2 = head;

	if (k > i)
		return ReverseList(head);

	if (k == i && P1 == NULL)
		return head;

	while (P1 != NULL)
	{
		P3 = P1;
		P4 = P2;

		P1 = P1 -> next;
		P2 = P2 -> next;
	}

	P4 -> next = NULL;
	P3 -> next = head;

	return P2;
}

int GetLengthOfList(List L)
{
	if (L == NULL)
		return 0;

	int i;

	i = 0;
	while (L != NULL)
	{
		L = L -> next;
		++i;
	}

	return i;
}

struct ListNode* rotateRight(struct ListNode* head, int k) {
	if (head == NULL || head -> next == NULL || k <= 0)
		return head;

	int Len;

	Len = GetLengthOfList(head);

	return RotateWithPosition(head, k % Len == 0 ? Len : k % Len);
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

	L1 = CreateList(1);
  PrintList(L1);

  L1 = rotateRight(L1, 2);
  PrintList(L1);

  // L2 = ReverseList(L2);
  // PrintList(L2);
	return 0;
}