// Given a singly linked list, determine if it is a palindrome.
// Follow up:
// Could you do it in O(n) time and O(1) space?

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

void DisconnectList(List L, List *Head1, List *Head2)
{
	Position P1, P2;
	Position PtrPre, PtrCur, PtrNext;

	P1 = P2 = L;
	PtrPre = P2;
	PtrCur = P2 -> next;

	while (P1 != NULL)
	{
		if (P1 -> next == NULL)
			break;

		P1 = P1 -> next -> next;
		P2 = P2 -> next;

		PtrNext = PtrCur -> next;
		PtrCur -> next = PtrPre;
		PtrPre = PtrCur;
		PtrCur = PtrNext;
	}

	L -> next = NULL;

	if (P1 == NULL)
	{
		P1 = PtrPre -> next;
		PtrPre -> next = PtrCur;
		*Head1 = P1;
		*Head2 = PtrPre;
	}
	else
	{
		*Head1 = PtrPre -> next;
		*Head2 = PtrCur;
	}

	return;
}

int isPalindrome(struct ListNode* head) {
	if (head == NULL || head -> next == NULL)
		return 1;

	List Head1, Head2;
	DisconnectList(head, &Head1, &Head2);

	while (Head1 != NULL && Head2 != NULL)
	{
		if (Head1 -> val != Head2 -> val)
			return 0;

		Head1 = Head1 -> next;
		Head2 = Head2 -> next;
	}

	if (Head1 == NULL || Head2 == NULL)
		return 1;

	return 0;
}

int main(int argc, char const *argv[])
{
	List L1, L2;
	List Head1, Head2;
	Position P;

	L1 = CreateList(3);
	L2 = CreateReversedList(5);
	PrintList(L1);
	PrintList(L2);

	for (P = L1; P -> next != NULL; P = P -> next);
	// P -> next = NewListNode(10);
	// P = P -> next;
	P -> next = L2;
	PrintList(L1);

	// DisconnectList(L1, &Head1, &Head2);
	// PrintList(Head1);
	// PrintList(Head2);

	printf("%d\n", isPalindrome(L1));
	return 0;
}