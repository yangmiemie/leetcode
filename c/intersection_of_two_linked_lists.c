// Write a program to find the node at which the intersection of two singly linked lists begins.


// For example, the following two linked lists:

// A:          a1 → a2
//                    ↘
//                      c1 → c2 → c3
//                    ↗            
// B:     b1 → b2 → b3
// begin to intersect at node c1.


// Notes:

// If the two linked lists have no intersection at all, return null.
// The linked lists must retain their original structure after the function returns.
// You may assume there are no cycles anywhere in the entire linked structure.
// Your code should preferably run in O(n) time and use only O(1) memory.

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

int GetLengthOfList(List L)
{
	int i;

	i = 0;

	while (L != NULL)
	{
		L = L -> next;
		++i;
	}

	return i;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
	int Len1, Len2, i;

	if (headA == NULL || headB == NULL)
		return NULL;

	Len1 = GetLengthOfList(headA);
	Len2 = GetLengthOfList(headB);
	
	if (Len1 > Len2)
	{
		for (i = 0; i < Len1 - Len2; ++i)
			headA = headA -> next;
	}

	if (Len2 > Len1)
	{
		for (i = 0; i < Len2 - Len1; ++i)
			headB = headB -> next;
	}

	while (headA != NULL)
	{
		if (headA -> val == headB -> val)
			return headA;

		headA = headA -> next;
		headB = headB -> next;
	}

	return NULL;
}

int main(int argc, char const *argv[])
{
	List L1, L2, L3;
	Position P;

  L1 = CreateList(3);
  PrintList(L1);

  L2 = CreateList(5);
  PrintList(L2);
  
  L3 = CreateList(2);
  PrintList(L3);

	for (P = L1; P -> next != NULL; P = P -> next);
	P -> next = L3;

  PrintList(L1);

 	for (P = L2; P -> next != NULL; P = P -> next);
	P -> next = L3; 

  PrintList(L2);
	
	printf("%d\n", getIntersectionNode(L1, L2) -> val);
	return 0;
}