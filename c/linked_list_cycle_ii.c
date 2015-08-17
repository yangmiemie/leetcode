// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

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

Position GetNodeOfCycle(List Head)
{
	Position P1, P2;
	
	P1 = P2 = Head;

	while (P1 != NULL)
	{
		P2 = P2 -> next;
		if (P1 -> next == NULL)
			return NULL;
		P1 = P1 -> next -> next;

		if (P1 == P2)
			return P1;
	}

	return NULL;
}

int GetLengthOfList(List L)
{
	int i;

	i = 0;

	while (L != NULL)
	{
		++i;
		L = L -> next;
	}

	return i;
}

Position GetIntersectionOfLists(List L1, List L2)
{
	int Len1, Len2, i;

	Len1 = GetLengthOfList(L1);
	Len2 = GetLengthOfList(L2);

	if (Len1 > Len2)
	{
		for (i = 0; i < Len1 - Len2; ++i)
			L1 = L1 -> next;
	}

	if (Len1 < Len2)
	{
		for (i = 0; i < Len2 - Len1; ++i)
			L2 = L2 -> next;
	}

	while (L1 != NULL)
	{
		if (L1 == L2)
			return L1;

		L1 = L1 -> next;
		L2 = L2 -> next;
	}

	return NULL;
}

struct ListNode *detectCycle(struct ListNode *head) {
	if (head == NULL)
		return NULL;

	Position CycleNode;
	List NewHead;
	CycleNode = GetNodeOfCycle(head);

	if (CycleNode == NULL)
		return NULL;

	NewHead = CycleNode -> next;
	CycleNode -> next = NULL;

	return GetIntersectionOfLists(head, NewHead);
}

int main(int argc, char const *argv[])
{
	List L;
  Position P1, P2;
  int i;

  L = CreateList(15);
  PrintList(L);

 //  for (P1 = L; P1 -> next != NULL; P1 = P1 -> next);
 //  P2 = L;
	// for (i = 0; i < 1; ++i)
	// 	P2 = P2 -> next;
	// P1 -> next = P2;

	printf("%d\n", detectCycle(L) -> val);
	return 0;
}