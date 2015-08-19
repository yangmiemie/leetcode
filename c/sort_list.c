// Sort a linked list in O(n log n) time using constant space complexity.

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

List Split(List L)
{
	if (L == NULL || L -> next == NULL)
		return L;

	Position P1, P2, P3;
	List L1;
	P1 = P2 = L;

	while (P1 != NULL)
	{
		if (P1 -> next == NULL)
			break;

		P1 = P1 -> next -> next;
		P3 = P2;
		P2 = P2 -> next;
	}

	L1 = P3 -> next;
	P3 -> next = NULL;
	return L1;
}

List MergeSortedList(List L1, List L2)
{
	if (L1 == NULL)
		return L2;

	if (L2 == NULL)
		return L1;

	Position P1, P2, P;
	List L;

	if (L1 -> val < L2 -> val)
	{
		L = L1;
		L1 = L1 -> next;		
	}
	else
	{
		L = L2;
		L2 = L2 -> next;		
	}

	P = L;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1 -> val < L2 -> val)
		{
			P -> next = L1;
			L1 = L1 -> next;
			P = P -> next;
		}
		else
		{
			P -> next = L2;
			L2 = L2 -> next;
			P = P -> next;
		}
	}

	if (L1 != NULL)
		P -> next = L1;

	if (L2 != NULL)
		P -> next = L2;

	return L;
}

struct ListNode* sortList(struct ListNode* head) {
	if (head == NULL || head -> next == NULL)
		return head;

	List L;

	L = Split(head);
	head = sortList(head);
	L = sortList(L);

	return MergeSortedList(head, L);  
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

	L1 = CreateEvenList(1);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  L = Split(L1);
  PrintList(L1);
  PrintList(L);
  L2 = MergeSortedList(L, L1);
	PrintList(L2);

	L1 = CreateRandList(1);
  PrintList(L1);
	L1 = sortList(L1);
  PrintList(L1);
	return 0;
}