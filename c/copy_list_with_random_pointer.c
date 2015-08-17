// A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

// Return a deep copy of the list.

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     struct RandomListNode *next;
 *     struct RandomListNode *random;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

struct RandomListNode {
	int label;
  struct RandomListNode *next;
  struct RandomListNode *random;
};

typedef struct RandomListNode* Position;
typedef struct RandomListNode* List;

Position NewRandomListNode(int Value)
{
	Position P;

	P = malloc(sizeof(struct RandomListNode));
	P -> next = P -> random = NULL;
	P -> label = Value;

	return P;
}

List CloneRandomList(List L)
{
	Position P, NewNode;
	
	P = L;
	while (P != NULL)
	{
		NewNode = NewRandomListNode(P -> label);
		NewNode -> next = P -> next;
		P -> next = NewNode;
		P = P -> next -> next;
	}

	return L;
}

List ConnectRandPointer(List L)
{
	Position P;

	P = L;
	while (P != NULL)
	{
		if (P -> random == NULL)
			P -> next -> random = NULL;
		else
			P -> next -> random = P -> random -> next;
	
		P = P -> next -> next;
	}

	return L;
}

List DisconnectList(List L)
{
	Position P1, P2;
	List NewList;

	NewList = L -> next;
	P1 = L;
	P2 = NewList;

	while (P1 != NULL)
	{
		P1 -> next = P1 -> next -> next;
		if (P2 -> next != NULL)
			P2 -> next = P2 -> next -> next;
		else
			P2 -> next = NULL;

		P1 = P1 -> next;
		P2 = P2 -> next;
	}

	return NewList;
}

struct RandomListNode *copyRandomList(struct RandomListNode *head) {
	List L;

	if (head == NULL)
		return NULL;

	L = CloneRandomList(head);
	L = ConnectRandPointer(L);
	return DisconnectList(L);
}

void PrintList(List L)
{
  while (L != NULL)
  {
    printf("%d ", L -> label);
    L = L -> next;
  }

  printf("\n");
}

int main(int argc, char const *argv[])
{
	int i;
	List L, L2;
	Position P;

	L = NewRandomListNode(-1);
	P = L;
	for (i = 1; i < 0; ++i)
	{
		P -> next = NewRandomListNode(i);
		P = P -> next;		
	}

	PrintList(L);

	P = L;
	while (P != NULL)
	{
		if (P -> next)
			P -> random = P -> next -> next;
		else
			P -> random = NULL;

		P = P -> next;
	}

	L2 = copyRandomList(L);
	PrintList(L2);
	return 0;
}