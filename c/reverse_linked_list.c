// Reverse a singly linked list.

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

List ReverseListRecursively(List L, List* Head)
{
	if (L -> next == NULL)
	{
		*Head = L;
		return L;
	}	

	Position P;
	P = ReverseListRecursively(L -> next, Head);
	P -> next = L;
	P = P -> next;
	return P;
}

List ReverseList1(List L)
{
	List Head;
	L = ReverseListRecursively(L, &Head);
	L -> next = NULL;
	return Head;
}

List ReverseList2(List L)
{
	Position PtrCur, PtrPre, PtrNext;

	if (L -> next == NULL)
		return L;

	PtrPre = L;
	PtrCur = L -> next;
	PtrPre -> next = NULL;

	while (PtrCur != NULL)
	{
		PtrNext = PtrCur -> next;
		PtrCur -> next = PtrPre;
		PtrPre = PtrCur;
		PtrCur = PtrNext;
	}

	return PtrPre;
}

struct ListNode* reverseList(struct ListNode* head) {
	if (head == NULL)
		return NULL;

	if (rand() % 2 == 1)
		return ReverseList1(head);
	else
		return ReverseList2(head);
}

int main(int argc, char const *argv[])
{
	List L1, L2;

	L1 = CreateReversedList(15);
	PrintList(L1);

	L1 = reverseList(L1);
	PrintList(L1);
	return 0;
}