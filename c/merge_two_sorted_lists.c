// Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

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

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	List L;
	Position P;

	if (l1 == NULL)
		return l2;

	if (l2 == NULL)
		return l1;

	if (l1 -> val > l2 -> val)
	{
		L = l2;
		l2 = l2 -> next;
	}
	else
	{
		L = l1;
		l1 = l1 -> next;
	}
	
	P = L;

	while (l2 != NULL && l1 != NULL)
	{
		if (l1 -> val < l2 -> val)
		{
			P -> next = l1;
			l1 = l1 -> next;
		}
		else
		{
			P -> next = l2;
			l2 = l2 -> next;
		}

		P = P -> next;
	}

	if (l1 != NULL)
		P -> next = l1;

	if (l2 != NULL)
		P -> next = l2;

	return L;
}

int main(int argc, char const *argv[])
{
	List L1, L2, L;

	L1 = CreateEvenList(10);
	L2 = CreateOddList(10);
	PrintList(L1);
	PrintList(L2);

	L = mergeTwoLists(L1, L2);
	PrintList(L);
	return 0;
}