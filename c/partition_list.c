// Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

// You should preserve the original relative order of the nodes in each of the two partitions.

// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.

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
  return S -> Capacity == S -> Size;
}

int IsEmpty(Stack S)
{
  return S -> Size == 0;
}

void Push(Stack S, ElementType Value)
{
  if (IsFull(S))
  {
    S -> Next = realloc(S -> Next, S -> Capacity * 2 * sizeof(ElementType));
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

void Swap(Position P1, Position P2)
{
  int Temp;

  Temp = P1 -> val;
  P1 -> val = P2 -> val;
  P2 -> val = Temp;
}

struct ListNode* partition2(struct ListNode* head, int x) {
  if (head == NULL)
    return NULL;

  Position P, P1, P2;
  Stack S;

  S = Initialize(16);
  P = head;
  while (P != NULL)
  {
    Push(S, P);
    P = P -> next;
  } 

  while (!IsEmpty(S))
  {
    P = Pop(S);

    if (P -> val >= x)
    {
      while (P -> next != NULL)
      {
        if (P -> next -> val < x)
        {
          Swap(P, P -> next);
          P = P -> next;
        } 
        else
        {
          break;
        }
      } 
    }
  }

  return head;
}

struct ListNode* partition(struct ListNode* head, int x) {
  if (head == NULL)
    return NULL;

  List FakeHead;
  Position P1, P2, P3;

  FakeHead = NewListNode(-1);
  FakeHead -> next = head;

  P1 = NULL;
  for (P2 = FakeHead; P2 != NULL && P2 -> next != NULL; )
  {
    if (P1 == NULL && P2 -> next -> val >= x)
    {
      P1 = P2;
    }
    if (P1 != NULL && P2 -> next -> val < x)
    {
      P3 =  P2 -> next -> next;
      P2 -> next -> next = P1 -> next;
      P1 -> next = P2 -> next;
      P2 -> next = P3;
      P1 = P1 -> next;
      continue;
    }

    P2 = P2 -> next;
  }

  P1 = FakeHead -> next;
  free(FakeHead);
  return P1;
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

  L1 = partition(L1, 2);
  PrintList(L1);
  return 0;
}