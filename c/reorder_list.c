// Given a singly linked list L: L0→L1→…→Ln-1→Ln,
// reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

// You must do this in-place without altering the nodes' values.

// For example,
// Given {1,2,3,4}, reorder it to {1,4,2,3}.

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
typedef struct StackRecord* Stack;

#define ElementType Position
#define MAX 16

struct StackRecord
{
	int Size;
	int Capacity;
	ElementType* Next;
};

Stack Initialize(int Capacity)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = Capacity;
	S -> Next = malloc(sizeof(ElementType) * Capacity);

	return S;
}

int IsFull(Stack S)
{
	return S -> Size == S -> Capacity;
}

int IsEmpty(Stack S)
{
	return S -> Size == 0;
}

void Push(Stack S, ElementType Value)
{
	if (IsFull(S))
	{
		S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = Value;
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[--S -> Size];
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

void reorderList(struct ListNode* head) {
	if (head == NULL || head -> next == NULL)
		return;

	Position P1, P2, P3;
	Stack S;

	P1 = P2 = head;

	while (P1 != NULL)
	{
		if (P1 -> next == NULL)
			break;

		P1 = P1 -> next -> next;
		P2 = P2 -> next;
	}

	P1 = P2 -> next;
	P2 -> next = NULL;

	S = Initialize(MAX);

	while (P1 != NULL)
	{
		Push(S, P1);
		P1 = P1 -> next;
	}

	P1 = head;

	while (!IsEmpty(S))
	{
		P2 = Pop(S);
		P3 = P1 -> next;
		P1 -> next = P2;
		P2 -> next = P3;
		P1 = P2 -> next;
	}

	return;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

	L1 = CreateEvenList(1);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  reorderList(L1);
  PrintList(L1);
	return 0;
}